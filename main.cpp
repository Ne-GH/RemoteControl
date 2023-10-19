#include <QApplication>
#include <QPushButton>
import Tmp;

int main(int argc, char *argv[]) {
    Func();
    QApplication a(argc, argv);
    QPushButton button("Hello world!", nullptr);
    button.resize(200, 100);
    button.show();
    return QApplication::exec();
}
