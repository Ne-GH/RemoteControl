/*******************************************************************************
 * Author : yongheng
 * Data   : 2023/10/20 22:25
*******************************************************************************/

#pragma once

#include <QWidget>
#include <QMainWindow>
#include <QThread>

namespace Ui { class MainWindow; }

class MainWindow : public QMainWindow {
    Q_OBJECT
    Ui::MainWindow *ui = nullptr;
    bool is_running = true;
    enum class ShowType {
        Screen,
        Camera
    };
    ShowType show_type = ShowType::Camera;
public:
    QThread *show_thread = nullptr;
    explicit MainWindow(QWidget *prent = nullptr);

    void Close();

    ~MainWindow() ;



};
