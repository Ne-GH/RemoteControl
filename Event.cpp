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

CursorState::CursorState() {
    auto pos = QCursor::pos();
    x = pos.x();
    y = pos.y();
}

OptionalState::OptionalState() {
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
void GetKeysState(OptionalState &optional_state) {
#define GET_KEY_STATE(key) optional_state.keys_state[key] = GetAsyncKeyState(key) & 0x8000

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
    auto tcp_server = new QTcpServer();
    tcp_server->listen(QHostAddress::Any, 8888);

    QObject::connect(tcp_server, &QTcpServer::newConnection, [=] {
        auto socket = tcp_server->nextPendingConnection();

        socket->write("hello");

        QObject::connect(socket, &QTcpSocket::readyRead, [=] {
            std::cout << "there is Server, get";
            QByteArray data = socket->readAll();
            std::cout << data.data() << std::endl;

		});


	});
}

void Display::run() {
    is_running = true;




    //while (is_running) {

    //}

}
