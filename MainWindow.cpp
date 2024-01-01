#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QLabel>
#include "Event.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

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
