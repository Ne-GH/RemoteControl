/*******************************************************************************
 * Author : yongheng
 * Data   : 2024/01/01
*******************************************************************************/

#include "Controlled.h"
#include <QThread>
#include <iostream>
#include "Event.h"

#include <QtNetwork>

static void Print(char* str,size_t size = 20) {
    for (int i = 0; i < size; ++i) {
        std::cout << (int)(unsigned char)str[i] << " ";
    }
    std::cout << std::endl;
}

SendScreenShot::SendScreenShot() {
    socket = new QTcpSocket();
	socket->connectToHost("127.0.0.1", 8888);
    connect(socket, &QTcpSocket::connected, [&] {

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
            Print(image_arr.data());
            Print(send_arr.data());
            socket->write(send_arr);


            socket->flush();

            std::this_thread::sleep_for(std::chrono::milliseconds{ 20 });
        }
	});
}

void SendScreenShot::run() {
  //  is_running = true;
  //  std::cout << '1' << std::endl;
  //  socket->connectToHost("127.0.0.1", 8888);


  //  while (socket->state() != QAbstractSocket::ConnectedState)
		//std::cout << '2' << std::endl;
  //      //;   //  尚未连接成功,等待连接

  //  while (is_running) {
  //      ScreenShot ss;
  //      QByteArray block;
  //      QDataStream out(&block, QIODevice::WriteOnly);
  //      out.setVersion(QDataStream::Qt_4_6);
  //      out.setByteOrder(QDataStream::BigEndian);
  //      out << (long long) 0;
  //      out << ss.pixmap;
  //      out.device()->seek(0);
  //      long long total = block.size() - sizeof(long long);
  //      out << total;
  //      std::cout << total << std::endl;
  //      socket->write(block);


  //      socket->flush();

  //      std::this_thread::sleep_for(std::chrono::milliseconds{500});

  //  }

}


Controlled::Controlled() {
    // 开一个线程不断发送屏幕截图
    auto send_screen_shot = new SendScreenShot();
    send_screen_shot->start();

    // 开个线程
    // while(true) 接收按键和鼠标信息并模拟

}

