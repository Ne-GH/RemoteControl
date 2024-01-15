/*******************************************************************************
 * Author : yongheng
 * Data   : 2024/01/01
*******************************************************************************/

#include "Controlled.h"
#include <QThread>
#include <iostream>
#include <thread>
#include "Event.h"

#include <QtNetwork>

void SendScreenShot::SendMessage () {
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


Controlled::Controlled() {
    // 开一个线程不断发送屏幕截图
    auto send_screen_shot = new SendScreenShot();
    auto send_message_thread = new QThread();
    send_screen_shot->moveToThread(send_message_thread);
	std::cout << "init : " << QThread::currentThreadId() << std::endl;
    QObject::connect(send_screen_shot, &SendScreenShot::SendMessageSig,send_screen_shot,&SendScreenShot::SendMessage);
    send_message_thread->start();
    // send_screen_shot->Send();

    // 开个线程
    // while(true) 接收按键和鼠标信息并模拟

}

