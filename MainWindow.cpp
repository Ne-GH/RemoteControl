#include "MainWindow.h"
#include "./ui_MainWindow.h"

#include <QLabel>
#include <QLineEdit>


#include "Event.h"
#include "Client/Control/Control.h"
#include "Client/Controlled/Controlled.h"

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    QObject::connect(ui->listen, &QPushButton::clicked, [this] {
        auto port = ui->listen_port->text();

		auto show_lab = new QLabel(this);
		setCentralWidget(show_lab);
		show_lab->setSizePolicy(QSizePolicy::Ignored, QSizePolicy::Ignored);
        auto control = new Control(show_lab,port);
	});

    QObject::connect(ui->connect, &QPushButton::clicked, [this] {   
        auto input = ui->socket_addr->text();
        auto list = input.split(':');
        auto addr = list[0];
        auto port = list[1];
        qDebug() << addr << " " << port;
        auto p = new Controlled(addr,port);
	});

}

MainWindow::~MainWindow() {
    delete ui;
}
