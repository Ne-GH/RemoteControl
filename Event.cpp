/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/12/31
*******************************************************************************/

#include "Event.h"

#include <QGuiApplication>
#include <QScreen>
#include <QCursor>
#include <iostream>
#include <QtNetwork>

ScreenShot::ScreenShot() {
    auto screen = QGuiApplication::primaryScreen();
    pixmap = screen->grabWindow(0);
}


// 根据不同的平台定义GET_KEY_STATE接口
#if WIN32
#include <Windows.h>
#else
#endif

void GetKeysState(std::bitset<255> &keys_state) {

#if WIN32
#define GET_KEY_STATE(key) keys_state[key] = GetAsyncKeyState(key) & 0x8000
#else
#define GET_KEY_STATE(key) key;
#define VK_LBUTTON 1
#define VK_RBUTTON 2
#endif

    // 左右鼠标，1-2
    GET_KEY_STATE(VK_LBUTTON);
    GET_KEY_STATE(VK_RBUTTON);

    // 0-9, 48-57
    GET_KEY_STATE('0');
    GET_KEY_STATE('1');
    GET_KEY_STATE('2');
    GET_KEY_STATE('3');
    GET_KEY_STATE('4');
    GET_KEY_STATE('5');
    GET_KEY_STATE('6');
    GET_KEY_STATE('7');
    GET_KEY_STATE('8');
    GET_KEY_STATE('9');

    // A-Z,65-90
    GET_KEY_STATE('A');
    GET_KEY_STATE('B');
    GET_KEY_STATE('C');
    GET_KEY_STATE('D');
    GET_KEY_STATE('E');
    GET_KEY_STATE('F');
    GET_KEY_STATE('G');
    GET_KEY_STATE('H');
    GET_KEY_STATE('I');
    GET_KEY_STATE('J');
    GET_KEY_STATE('K');
    GET_KEY_STATE('L');
    GET_KEY_STATE('M');
    GET_KEY_STATE('N');
    GET_KEY_STATE('O');
    GET_KEY_STATE('P');
    GET_KEY_STATE('Q');
    GET_KEY_STATE('R');
    GET_KEY_STATE('S');
    GET_KEY_STATE('T');
    GET_KEY_STATE('U');
    GET_KEY_STATE('V');
    GET_KEY_STATE('W');
    GET_KEY_STATE('X');
    GET_KEY_STATE('Y');
    GET_KEY_STATE('Z');


#undef GET_KEY_STATE
}

// 构造函数中就构造出了按键的状态表
EventState::EventState() {
    cursor_x = cursor_y = 0;
    keys_state.reset();
}
void EventState::GetCurKeysEvent() {
    auto pos = QCursor::pos();
    cursor_x = pos.x();
    cursor_y = pos.y();
    keys_state.reset();
    GetKeysState(keys_state);
}
void EventState::Reset() {
    cursor_x = cursor_y = 0;
    keys_state.reset();
}




void SendKeysState(QTcpSocket *socket) {
        EventState event_state;
        event_state.GetCurKeysEvent();
        QByteArray send_arr;
        QDataStream out(&send_arr,QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out.setByteOrder(QDataStream::BigEndian);
        out << 0ll; // 总长度
        out << event_state.cursor_x;
        out << event_state.cursor_y;
        out << event_state.keys_state.to_string().c_str();

        out.device()->seek(0);
        long long total = send_arr.size() - sizeof(long long);
        out << total;


        socket->write(send_arr);
        socket->flush();
}



Display::Display(QLabel* arg_display_lab,QString port) : display_lab(arg_display_lab) {
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, port.toInt());

    QObject::connect(server, &QTcpServer::newConnection, [&] {
        socket = server->nextPendingConnection();
        std::cout << "new connect" << std::endl;
        QObject::connect(socket, &QTcpSocket::readyRead, [&] {
            static long long total_size = 0;
            static QByteArray arr;
            QDataStream in(socket);
            in.setVersion(QDataStream::Qt_4_6);
            in.setByteOrder(QDataStream::BigEndian);

            static EventState event_state;

            if (total_size == 0) {
                if (socket->bytesAvailable() < sizeof(long long))
                    return;
                in >> total_size;
            }

            if (socket->bytesAvailable() < total_size)
                return;

            arr.clear();
            arr = socket->read(total_size);
            // 处理arr
            if (arr.size() == total_size) {
                QByteArray image_arr = QByteArray::fromBase64(arr.data()+4);
                QImage image;
                if (!image.loadFromData(image_arr, "jpg")) {
                    std::cout << "error load" << std::endl;
                }
                else {
                    QPixmap pixmap = QPixmap::fromImage(image);
                    display_lab->setPixmap(pixmap.scaled(display_lab->size(), Qt::KeepAspectRatio));
                }

                arr.clear();
                total_size = 0;

                // 接收完被控制端的屏幕数据之后，发送按键状态
                SendKeysState(socket);
                std::cout << "发送了按键状态" << std::endl;
            }
            else {
                std::cout << "123" << std::endl;
            }

		});
	});
}

void SendScreenShot::Send() {
    std::cout << QThread::currentThreadId() << std::endl;
    while (1) {
        ScreenShot ss;
        QByteArray send_arr;
        QDataStream out(&send_arr, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);
        out.setByteOrder(QDataStream::BigEndian);
        out << 0ll;

        QByteArray image_arr;
        QBuffer buf(&image_arr);
        ss.pixmap.save(&buf, "jpg");
        image_arr = image_arr.toBase64();

        out << image_arr;
        out.device()->seek(0);
        long long total = send_arr.size() - sizeof(long long);
        out << total;
        socket->write(send_arr);

        socket->flush();

        std::this_thread::sleep_for(std::chrono::milliseconds{ 20 });
    }
}


// 调用Send发送屏幕信息，并接收按键信息
SendScreenShot::SendScreenShot(QString addr,QString port) {
    socket = new QTcpSocket();
    socket->connectToHost(addr, port.toInt());
    connect(socket, &QTcpSocket::connected, [this] {
        emit SendMessageSig();

        // 接收控制端传来的按键状态
        // 总长度，鼠标x，y ，(QDataStream 自带的字符串长度), bitset<255>转来的字符串
        QObject::connect(socket, &QTcpSocket::readyRead, [&] {
            static long long total_size = 0;
            static QByteArray arr;
            QDataStream in(socket);
            in.setVersion(QDataStream::Qt_4_6);
            in.setByteOrder(QDataStream::BigEndian);

            if (total_size == 0) {
                if (socket->bytesAvailable() < sizeof(long long))
                    return;
                in >> total_size;
            }

            if (socket->bytesAvailable() < total_size)
                return;

            // cursor x,y
            int x, y;
            in >> x >> y;

            arr.clear();
            arr = socket->read(total_size - sizeof(int)*2);
            std::string keys_str(arr.data() + 4);

            // 控制端的按键状态和鼠标状态
            EventState event_state;
            event_state.cursor_x = x;
            event_state.cursor_y = y;
            event_state.keys_state = std::bitset<255>(keys_str);

            // 在此处接收时进行模拟

            arr.clear();
            total_size = 0;
		});
	});
}
