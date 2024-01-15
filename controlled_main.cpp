#include "MainWindow.h"

#include <QThread>
#include <QApplication>
#include <QLabel>
#include <QStatusBar>
#include <QTimer>
#include <iostream>
#include "Event.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w(UserType::CONTROLLED);
    w.setWindowTitle("beikongzhi");
    w.show();
    std::cout << "main : " << QThread::currentThreadId() << std::endl;
    return QApplication::exec();
}
