/*******************************************************************************
 * Author : yongheng
 * Data   : 2024/01/01
*******************************************************************************/

#include "Control.h"



Control::Control(QLabel *lab) {
    // 开个线程
    // while(true)  接收屏幕信息并显示
    auto dp = new Display(lab);
    dp->start();

    QObject::connect(dp, &Display::display, [=](QPixmap pixmap) {
        emit display(pixmap);
	});


    // 开个线程
    // while(true)  监听按键和鼠标信息
        // 检查当前有无鼠标信息
        // 检查当前有无按键信息
        // 将获取的信息封装为event
        // 将event序列化
        // 发送出去

    // 或者
    // 全局的key，默认为空
    // connect (按键信息),修改key
    // 将key的数据和鼠标信息封装到event中
    // 将key的数据修改为空

}
