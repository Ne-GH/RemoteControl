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




Controlled::Controlled() {
    // 开一个线程不断发送屏幕截图
    auto send_screen_shot = new SendScreenShot();
    auto send_message_thread = new QThread();
    send_screen_shot->moveToThread(send_message_thread);
	std::cout << "init : " << QThread::currentThreadId() << std::endl;
    QObject::connect(send_screen_shot, &SendScreenShot::SendMessageSig,send_screen_shot,&SendScreenShot::Send);
    send_message_thread->start();

}

