#pragma once

#include <QMainWindow>

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

enum class UserType {
    CONTROL,CONTROLLED
};

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    MainWindow(UserType user_type,QWidget *parent = nullptr);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
};
