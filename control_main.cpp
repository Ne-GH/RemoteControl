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
    // 开线程，监听key
    // 并做其他处理

    QTimer timer;
    QObject::connect(&timer,&QTimer::timeout,[&]{
        CursorState cursor_state;
        w.statusBar()->showMessage((std::to_string(cursor_state.x) + " , " + std::to_string(cursor_state.y)).c_str());
    });
    timer.start(100);



    return QApplication::exec();
}
