#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QLabel>


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



    // 控制端
    if (user_type == UserType::CONTROL) {
        auto control = new Control(show_lab);
        ScreenShot ss;
        show_lab->setPixmap(ss.pixmap.scaled(show_lab->size(),Qt::KeepAspectRatio));
    }

    // 被控制端
    else if (user_type == UserType::CONTROLLED) {
        auto p = new Controlled();
    }
}

MainWindow::~MainWindow() {
    delete ui;
}
