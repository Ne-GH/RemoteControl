/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/12/31
*******************************************************************************/

#pragma once

#include <QThread>
#include <QLabel>
#include <QPixmap>
#include <bitset>
#include <QtNetwork>

/*******************************************************************************
 * 构造函数即获取屏幕截图，并保存在pixmap成员中
*******************************************************************************/
struct ScreenShot {
public:
    QPixmap pixmap;
    ScreenShot();
};

struct EventState {
    std::bitset<255> keys_state{};
    int cursor_x{}, cursor_y{};
    EventState();
};


struct ListenEvent : QThread {
    bool is_running = false;
    EventState keys_state;
public:
    ListenEvent();
    void run() override;
};
struct Display : QThread {
    Q_OBJECT

private:
    QLabel* display_lab = nullptr;
    bool is_running = false;
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;

signals:
    void display(QPixmap pixmap);

public:
    Display(QLabel *);
    void run() override;
};
