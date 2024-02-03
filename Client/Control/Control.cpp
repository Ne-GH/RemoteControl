/*******************************************************************************
 * Author : yongheng
 * Data   : 2024/01/01
*******************************************************************************/

#include "Control.h"



Control::Control(QLabel *lab,QString port) {
    // 开个线程
    // while(true)  接收屏幕信息并显示
    auto dp = new Display(lab,port);

}
