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

static void GetKeysState(std::bitset<255> &keys_state) {

// 根据不同的平台定义GET_KEY_STATE接口
#if WIN32
    #include <Windows.h>
#define GET_KEY_STATE(key) keys_state[key] = GetAsyncKeyState(key) & 0x8000
#else
#define GET_KEY_STATE(key) 1;
    //keys_state['A'] = GetKeyState('A');
#endif

    GET_KEY_STATE('A');
    GET_KEY_STATE('B');
    GET_KEY_STATE('C');
    GET_KEY_STATE('D');
    GET_KEY_STATE('E');
    GET_KEY_STATE(VK_LBUTTON);
    GET_KEY_STATE(VK_RBUTTON);


#undef GET_KEY_STATE
}

// 构造函数中就构造出了按键的状态表
EventState::EventState() {
    auto pos = QCursor::pos();
    cursor_x = pos.x();
    cursor_y = pos.y();
    keys_state.reset();
    GetKeysState(keys_state);
}



// 获取鼠标位置和按键
// 获取键盘按键
// 整合为Event
// Event作为信号发出

ListenEvent::ListenEvent() {
    socket = new QTcpSocket();
    // 建立连接
    QObject::connect(socket,&QTcpSocket::connected,[this] {
        emit LoopSendKeysStateSig();
    });
}

void ListenEvent::LoopSendKeysState() {

    while (1) {
        EventState event_state;
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

        std::this_thread::sleep_for(std::chrono::milliseconds {20});
    }

}




Display::Display(QLabel* arg_display_lab) : display_lab(arg_display_lab) {
    server = new QTcpServer(this);
    server->listen(QHostAddress::Any, 8888);

    QObject::connect(server, &QTcpServer::newConnection, [&] {
        socket = server->nextPendingConnection();
        std::cout << "new connect" << std::endl;
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
                std::cout << "total : " << total_size << std::endl;
            }

            if (socket->bytesAvailable() < total_size)
                return;

            arr.clear();
            arr = socket->read(total_size);
            // 处理arr
            if (arr.size() == total_size) {
                std::cout << "size == total" << std::endl;
                
                QByteArray image_arr = QByteArray::fromBase64(arr.data()+4);
                QImage image;
                if (!image.loadFromData(image_arr, "jpg")) {
                    std::cout << "error load" << std::endl;
                }
                else {
                    QPixmap pixmap = QPixmap::fromImage(image);
                    display_lab->setPixmap(pixmap.scaled(display_lab->size(), Qt::KeepAspectRatio));
                    std::cout << "is ok" << std::endl;
                }

                arr.clear();
                total_size = 0;
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
        std::cout << total << std::endl;
        std::cout << "image total : " << total << std::endl;
        socket->write(send_arr);

        socket->flush();

        std::this_thread::sleep_for(std::chrono::milliseconds{ 20 });
    }
}

SendScreenShot::SendScreenShot() {
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 8888);
    connect(socket, &QTcpSocket::connected, [this] {
        emit SendMessageSig();
        });
}
