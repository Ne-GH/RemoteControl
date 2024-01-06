/*******************************************************************************
 * Author : yongheng
 * Data   : 2024/01/01
*******************************************************************************/

#pragma once


#include <QThread>
#include <QtNetwork>

// 被控制端，上传自己的屏幕信息或其他信息，接收控制端传来的键盘和鼠标操作，并进行模拟
class Controlled {
public:
    Controlled();
    

};

class SendScreenShot : public QThread {
    bool is_running = false;
public:
    SendScreenShot();
    void run() override;
};
