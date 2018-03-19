#include "mainwindow.h"
#include "ui_mainwindow.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{

    socket = new QTcpSocket();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    socket->close();
    delete ui;
}


////////////////////////////////////////
void MainWindow::on_connect_clicked()
{
    if(socket->isOpen()){
        socket->close();

        ui->connectLabel->setText("Disconnected");
        ui->connectLabel->setStyleSheet("color:red");

        ui->connect->setText("CONNECT");
    }else{
        socket->connectToHost("192.168.4.1", 80);

        if(socket->waitForConnected(3000)){
            ui->connectLabel->setText("Connected!");
            ui->connectLabel->setStyleSheet("color:green");

            ui->connect->setText("DISCONNECT");
        }else{
            ui->connectLabel->setText("Disconnected");
            ui->connectLabel->setStyleSheet("color:red");

            ui->connect->setText("CONNECT");
        }
    }


}


////////////////////////////////////////
void MainWindow::on_forward_pressed()
{
    socket->write("DIR:UP");
}

void MainWindow::on_forward_released()
{
    socket->write("DIR:STOP");
}


////////////////////////////////////////
void MainWindow::on_left_pressed()
{
    socket->write("DIR:LEFT");
}

void MainWindow::on_left_released()
{
    socket->write("DIR:STOP");
}


////////////////////////////////////////
void MainWindow::on_stop_clicked()
{
    socket->write("DIR:STOP");
}


////////////////////////////////////////
void MainWindow::on_right_pressed()
{
    socket->write("DIR:RIGHT");
}

void MainWindow::on_right_released()
{
    socket->write("DIR:STOP");
}


////////////////////////////////////////
void MainWindow::on_backward_pressed()
{
    socket->write("DIR:BACK");
}

void MainWindow::on_backward_released()
{
    socket->write("DIR:STOP");
}


////////////////////////////////////////
void MainWindow::on_speed_valueChanged(int value)
{
    socket->write(QString("SPEED:").append(QString::number(value)).toStdString().c_str());
}


////////////////////////////////////////
void MainWindow::on_color_valueChanged(int value)
{
    socket->write(QString("COLOR:").append(QString::number(value)).toStdString().c_str());
}


////////////////////////////////////////
void MainWindow::on_blink_clicked()
{
    socket->write("BLINK:TRUE");
}


////////////////////////////////////////
void MainWindow::on_sendText_clicked()
{
    socket->write(QString("TEXT:").append(ui->text->text()).toStdString().c_str());
}


////////////////////////////////////////
void MainWindow::on_clearText_clicked()
{
    ui->text->setText("");
}


////////////////////////////////////////
void MainWindow::on_towerUp_pressed()
{
    socket->write("TOWER:UP");
}

void MainWindow::on_towerUp_released()
{
    socket->write("TOWER:STOP");
}


////////////////////////////////////////
void MainWindow::on_towerLeft_pressed()
{
    socket->write("TOWER:LEFT");
}

void MainWindow::on_towerLeft_released()
{
    socket->write("TOWER:STOP");
}


////////////////////////////////////////
void MainWindow::on_shot_clicked()
{
    socket->write("SHOT:TRUE");
}


////////////////////////////////////////
void MainWindow::on_towerRight_pressed()
{
    socket->write("TOWER:RIGHT");
}

void MainWindow::on_towerRight_released()
{
    socket->write("TOWER:STOP");
}


////////////////////////////////////////
void MainWindow::on_towerDown_pressed()
{
    socket->write("TOWER:DOWN");
}

void MainWindow::on_towerDown_released()
{
    socket->write("TOWER:STOP");
}
