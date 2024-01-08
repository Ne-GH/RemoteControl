#include "MainWindow.h"

#include <QThread>
#include <QApplication>
#include <QLabel>
#include <QStatusBar>
#include <QTimer>
#include "Event.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w(UserType::CONTROL);
    w.setWindowTitle("kongzhi");
    w.show();
    return QApplication::exec();
}
