/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/12/31
*******************************************************************************/

#pragma once

#include <QThread>
#include <QLabel>
#include <QPixmap>
#include <bitset>

/*******************************************************************************
 * 构造函数即获取屏幕截图，并保存在pixmap成员中
*******************************************************************************/
struct ScreenShot {
public:
    QPixmap pixmap;
    ScreenShot();
};

struct CursorState {
    int key{};
    int x,y;
    CursorState();
};
struct KeysState {
    std::bitset<255> keys_state;
    KeysState();
};


struct ListenEvent : QThread {
    bool is_running = false;
    KeysState keys_state;
public:
    ListenEvent();
    void run() override;
};
struct Display : QThread {
    QLabel* display_lab = nullptr;
public:
    Display(QLabel *);
    void run() override;
};
