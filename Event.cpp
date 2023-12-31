/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/12/31
*******************************************************************************/

#include "Event.h"


ScreenShot::ScreenShot() {
    auto screen = QGuiApplication::primaryScreen();
    pixmap = screen->grabWindow(0);
}

CursorEvent::CursorEvent(int arg) : key(arg) {  }

KeyEvent::KeyEvent(int arg) : key(arg) {  }

EventListen::EventListen() {
    while (true) {
        // 获取屏幕;
        // 获取鼠标位置和按键
        // 获取键盘按键
        // 整合为Event
        // Event作为信号发出
    }
}
