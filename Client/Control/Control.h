/*******************************************************************************
 * Author : yongheng
 * Data   : 2024/01/01
*******************************************************************************/

#pragma once
#include "Event.h"

// 控制端，需要上传自己的键盘和鼠标操作，并获取被控制端的屏幕信息或其他信息
class Control : public QObject {
    Q_OBJECT


signals:
    void display(QPixmap pixmap);

public:
    Control(QLabel *);
   // 发出键盘和鼠标操作之后才上传信息

};
