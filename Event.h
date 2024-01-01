/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/12/31
*******************************************************************************/

#pragma once

#include <QThread>
#include <QScreen>
#include <QPixmap>
#include <QGuiApplication>

/*******************************************************************************
 * 构造函数即获取屏幕截图，并保存在pixmap成员中
*******************************************************************************/
struct ScreenShot {
public:
    QPixmap pixmap;
    ScreenShot();
};

struct CursorEvent {
    int key{};
    int x,y;
    CursorEvent();
};
struct KeyEvent {
    int key;
    KeyEvent();
};

struct Event {
    ScreenShot screen_shot;
    CursorEvent cursor_event;
    KeyEvent key_event;
    Event() = default;
};

