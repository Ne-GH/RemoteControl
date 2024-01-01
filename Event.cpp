/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/12/31
*******************************************************************************/

#include "Event.h"

#include <QCursor>

ScreenShot::ScreenShot() {
    auto screen = QGuiApplication::primaryScreen();
    pixmap = screen->grabWindow(0);
}

CursorEvent::CursorEvent() {
    auto pos = QCursor::pos();
    x = pos.x();
    y = pos.y();

}

KeyEvent::KeyEvent() {

}

// 获取鼠标位置和按键
// 获取键盘按键
// 整合为Event
// Event作为信号发出
