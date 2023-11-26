#include "MainWindow.h"
#include "Keys.h"
#include <QApplication>
#include <chrono>
#include <thread>


int main(int argc, char *argv[]) {
    QApplication a(argc, argv);
    auto window = new MainWindow;
    window->show();





    QObject::connect(&a,&QApplication::aboutToQuit,[=] {
        window->Close();
        window->show_thread->quit();
        window->show_thread->wait();
        delete window->show_thread;
        window->show_thread = nullptr;

    });
    return a.exec();
}
