#include "MainWindow.h"

#include <QApplication>
#include <QLabel>
#include "Event.h"

int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    MainWindow w;
    w.show();
    return QApplication::exec();
}
