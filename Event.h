﻿/*******************************************************************************
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
    void Reset();
    void GetCurKeysEvent();
};


struct ListenEvent : public QObject {
    Q_OBJECT
private:
    QTcpSocket *socket = nullptr;
public:
    ListenEvent();
    void LoopSendKeysState();
signals:
    void LoopSendKeysStateSig();
};

struct SimulateEvent : public QObject {
    Q_OBJECT
public:
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;
    SimulateEvent();

};


struct Display : public QObject {
    Q_OBJECT

private:
    QLabel* display_lab = nullptr;
    QTcpServer *server = nullptr;
    QTcpSocket *socket = nullptr;

public:
    Display(QLabel *,QString);
};

class SendScreenShot : public QObject {
    Q_OBJECT
public:
    QTcpSocket* socket = nullptr;
    SendScreenShot(QString,QString);
    void Send();

signals:
    void SendMessageSig();

};
