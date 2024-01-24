/*******************************************************************************
 * Author : yongheng
 * Data   : 2024/01/01
*******************************************************************************/

#include "Control.h"



Control::Control(QLabel *lab) {
    // 开个线程
    // while(true)  接收屏幕信息并显示
    auto dp = new Display(lab);

    // 开个线程，检测当前按键状态并发送
    auto listen_event = new ListenEvent();
    auto listen_event_thread = new QThread();
    listen_event->moveToThread(listen_event_thread);
    QObject::connect(listen_event,&ListenEvent::LoopSendKeysStateSig,listen_event,&ListenEvent::LoopSendKeysState);
    listen_event_thread->start();


}
