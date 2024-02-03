#include "MainWindow.h"

#include <QThread>
#include <QApplication>
#include <QLabel>
#include <QStatusBar>
#include <QTimer>
#include "Event.h"
int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.setWindowTitle("Remote Control");
    w.show();
    return QApplication::exec();
}
