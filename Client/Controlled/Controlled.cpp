/*******************************************************************************
 * Author : yongheng
 * Data   : 2024/01/01
*******************************************************************************/

#include "Controlled.h"
#include <QThread>
#include <iostream>

SendScreenShot::SendScreenShot() {
    auto tcp_socket = new QTcpSocket();
    tcp_socket->connectToHost("127.0.0.1", 8888);

    tcp_socket->write("message from client");
    QObject::connect(tcp_socket, &QTcpSocket::readyRead, [=] {
        std::cout << "client get";
        auto data = tcp_socket->readAll();
        std::cout << data.data() << std::endl;
	});
}

void SendScreenShot::run() {
    is_running = true;







    //while (is_running) {

    //}

}


Controlled::Controlled() {
    // 开一个线程不断发送屏幕截图
    auto send_screen_shot = new SendScreenShot();
    send_screen_shot->start();

    // 开个线程
    // while(true) 接收按键和鼠标信息并模拟

}

