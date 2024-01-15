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

EventState::EventState() {
    auto pos = QCursor::pos();
    cursor_x = pos.x();
    cursor_y = pos.y();
    keys_state.reset();

}

// 获取鼠标位置和按键
// 获取键盘按键
// 整合为Event
// Event作为信号发出

ListenEvent::ListenEvent() {

}

#if WIN32
#include <Windows.h>
void GetKeysState(EventState &event_state) {
#define GET_KEY_STATE(key) event_state.keys_state[key] = GetAsyncKeyState(key) & 0x8000

    //keys_state['A'] = GetKeyState('A');
    GET_KEY_STATE('A');
    GET_KEY_STATE('B');
    GET_KEY_STATE('C');
    GET_KEY_STATE('D');
    GET_KEY_STATE('E');
    GET_KEY_STATE(VK_LBUTTON);
    GET_KEY_STATE(VK_RBUTTON);
#undef GET_KEY_STATE
}
#else
void GetKeysState(EventState &event_state) {

}

#endif

void ListenEvent::run() {
    is_running = true;
#define COUT(key) std::cout << keys_state.keys_state[key] << ' ';

    while(is_running) {
        GetKeysState(keys_state);
        COUT('A');
        COUT('B');
        COUT('C');
        COUT('D');
//        COUT(VK_LBUTTON);
//        COUT(VK_RBUTTON);

        std::endl(std::cout);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
#undef COUT

}

static void Print(char* str) {
    for (int i = 0; i < 20; ++i) {
        std::cout << (int)(unsigned char)str[i] << " ";
    }
    std::cout << std::endl;
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
long long Reverse(long long src) {
    long long ret = 0;

    for (int i = 0; i < 8; ++i) {
        ret <<= 8;
        ret += src & 0xff;  //
        src >>= 8;
    }
    return ret;
}
void Display::run() {
    //is_running = true;

    //while (!socket)
    //    ;

    //QDataStream in(socket);
    //in.setVersion(QDataStream::Qt_4_6);
    //in.setByteOrder(QDataStream::BigEndian);
    //long long block_size = 0;


    //while (is_running) {
    //    //if (block_size == 0) {
    //    //    if (socket->bytesAvailable() < sizeof(long long))
    //    //        continue;
    //    //    // in >> block_size;
    //    //    QByteArray size_arr;
    //    //    size_arr = socket->read(sizeof(long long));
    //    //    memcpy(&block_size, size_arr.data(), sizeof(long long));
    //    //    block_size = Reverse(block_size);
    //    //    std::cout << block_size << std::endl;
    //    //}
    //    //if (socket->bytesAvailable() < block_size)
    //    //    continue;

    //    //std::cout << "block size : " << block_size << " "
    //    //    << "socket aviailable : " << socket->bytesAvailable() << std::endl;

    //    //QByteArray data;
    //    //data.resize(block_size);
    //    //in.readRawData(data.data(), block_size);
    //    //data = socket->read(block_size);
    //    QPixmap pixmap;
    //    in >> pixmap;
    //    // block_size = 0;
    //    display_lab->setPixmap(pixmap.scaled(display_lab->size(), Qt::KeepAspectRatio));
    //    // std::this_thread::sleep_for(std::chrono::seconds{5});
    //}

}
