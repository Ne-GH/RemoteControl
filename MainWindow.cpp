#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QLabel>

#include <VECTOR>

#include "Event.h"
#include "Client/Control/Control.h"
#include "Client/Controlled/Controlled.h"

MainWindow::MainWindow(UserType user_type,QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);



    // ¿ØÖÆ¶Ë
    if (user_type == UserType::CONTROL) {
        auto p = new Control();
    }
    // ±»¿ØÖÆ¶Ë
    else if (user_type == UserType::CONTROLLED) {
        auto p = new Controlled();
    }

    auto show_lab = new QLabel(this);
    show_lab->resize(size());

//    Event event;
//
//    event.screen_shot.pixmap = event.screen_shot.pixmap.scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
//    show_lab->setPixmap(event.screen_shot.pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}
