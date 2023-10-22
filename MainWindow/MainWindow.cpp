/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/20 22:25
*******************************************************************************/

#include "MainWindow.h"
#include "ui_MainWindow.h"

#include <QPushButton>

#include "Camera.h"

#include <QTimer>
#include "Cursor.h"

MainWindow::MainWindow(QWidget *prent) : QMainWindow(prent),ui(new Ui::MainWindow){
    ui->setupUi(this);

    auto camera = new Camera(ui->show_label);

    QTimer *timer = new QTimer();
    connect(timer,&QTimer::timeout,[=]{
        Cursor cursor;
        auto [x,y] = cursor.GetGlobalPos();
        qDebug() << x << ' ' << y ;

    });
    timer->start(100);




//    camera->Show();

//    show_thread = new QThread();
//    QObject::connect(ui->p1,&QPushButton::clicked,[=]{
//        is_running = true;
//        show_type = ShowType::Screen;
//        show_thread->start();
//    });
//
//    QObject::connect(ui->p2,&QPushButton::clicked,[=]{
//        is_running = false;
//        show_thread->quit();
//        show_thread->wait();
//
//        show_type = ShowType::Camera;
//
//        auto video_widget = new QVideoWidget(ui->show_label);
//        video_widget->resize(640, 480);
//        video_widget->show();
//
//        auto camera = new QCamera(QMediaDevices::defaultVideoInput());
//        camera->start();
//
//        auto mediaCaptureSession = new QMediaCaptureSession;
//        mediaCaptureSession->setCamera(camera);
//        mediaCaptureSession->setVideoOutput(video_widget);
//    });

//    QObject::connect(show_thread,&QThread::started,[=]{
//
//        while (is_running) {
//            if (show_type == ShowType::Screen) {
//
//                QScreen *screen = QGuiApplication::primaryScreen();
//                auto pixmap = screen->grabWindow(0).scaled(ui->show_label->size(), Qt::KeepAspectRatio);
//                ui->show_label->setPixmap(pixmap);
//            }
//            else {
//
//
//            }
//
//        }
//    });
}

MainWindow::~MainWindow() {
    is_running = false;

}

void MainWindow::Close() {
    is_running = false;

}


