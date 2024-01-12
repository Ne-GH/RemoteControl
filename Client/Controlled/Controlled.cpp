/*******************************************************************************
 * Author : yongheng
 * Data   : 2024/01/01
*******************************************************************************/

#include "Controlled.h"
#include <QThread>
#include <iostream>
#include "Event.h"

SendScreenShot::SendScreenShot() {
    socket = new QTcpSocket();
    socket->connectToHost("127.0.0.1", 8888);
//    QObject::connect(socket, &QTcpSocket::readyRead, [=] {
//        std::cout << "client get";
//        auto data = socket->readAll();
//        std::cout << data.data() << std::endl;
//	});
}

void SendScreenShot::run() {
    is_running = true;


    while (socket->state() != QAbstractSocket::ConnectedState)
        ;   //  尚未连接成功,等待连接

    while (is_running) {
        ScreenShot ss;
        QByteArray block;
        QDataStream out(&block, QIODevice::WriteOnly);
        out.setVersion(QDataStream::Qt_4_6);

        out << (qint64) 0;
        out << ss.pixmap;
        out.device()->seek(0);
        qint64 total = block.size() - sizeof(qint64);
        out << total;
        socket->write(block);

        socket->flush();

        std::this_thread::sleep_for(std::chrono::milliseconds(100));

    }

}


Controlled::Controlled() {
    // 开一个线程不断发送屏幕截图
    auto send_screen_shot = new SendScreenShot();
    send_screen_shot->start();

    // 开个线程
    // while(true) 接收按键和鼠标信息并模拟

}

