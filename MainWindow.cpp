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

    auto show_lab = new QLabel(this);
    show_lab->resize(size());



    // ¿ØÖÆ¶Ë
    if (user_type == UserType::CONTROL) {
        auto control = new Control(show_lab);
        ScreenShot ss;
        show_lab->setPixmap(ss.pixmap.scaled(show_lab->size(),Qt::KeepAspectRatio));
        QObject::connect(control, &Control::display, [=](QPixmap pixmap) {
            show_lab->setPixmap(pixmap);
		});


    }
    // ±»¿ØÖÆ¶Ë
    else if (user_type == UserType::CONTROLLED) {
        auto p = new Controlled();
    }


//    Event event;
//
//    event.screen_shot.pixmap = event.screen_shot.pixmap.scaled(size(),Qt::KeepAspectRatio,Qt::SmoothTransformation);
//    show_lab->setPixmap(event.screen_shot.pixmap);
}

MainWindow::~MainWindow()
{
    delete ui;
}
