/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/12/31
*******************************************************************************/

#include "Event.h"

#include <QGuiApplication>
#include <QScreen>
#include <QCursor>
#include <iostream>
#include <QtNetWork>

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
void GetKeysState(KeysState& keys_state) {

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
        COUT(VK_LBUTTON);
        COUT(VK_RBUTTON);

        std::endl(std::cout);

        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    }
#undef COUT

}



Display::Display(QLabel* arg_display_lab) : display_lab(arg_display_lab) {
    auto tcp_server = new QTcpServer(this);
    tcp_server->listen(QHostAddress::Any, 8888);

    QObject::connect(tcp_server, &QTcpServer::newConnection, [=] {
        
        auto socket = tcp_server->nextPendingConnection();
        std::cout << "new connect" << std::endl;

        QObject::connect(socket, &QTcpSocket::readyRead, [=] {
            QDataStream in(socket);
            in.setVersion(QDataStream::Qt_4_6);
            static qint64 block_size = 0;
            std::cout << block_size << std::endl;
            if (block_size == 0) {
                if (socket->bytesAvailable() < (int)sizeof(quint64)) 
                    return;

                in >> block_size;
				std::cout << block_size << std::endl;
            }
            if (socket->bytesAvailable() < block_size) 
                return;
            //如果没有得到全部的数据，则返回，继续接收数据
			QPixmap pixmap;
			in >> pixmap;
            block_size = 0;
			display_lab->setPixmap(pixmap.scaled(display_lab->size(), Qt::KeepAspectRatio));

		});


	});
}

void Display::run() {
    is_running = true;




    //while (is_running) {

    //}

}
