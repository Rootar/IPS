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

//////////////////////////////////////// CONNECTION ////////////////////////////////////////
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

//////////////////////////////////////// KEYBOARD ////////////////////////////////////////
////////////////////////////////////////
void MainWindow::keyPressEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_W && event->isAutoRepeat() == false){
        on_forward_pressed();
    }

    if(event->key() == Qt::Key_A && event->isAutoRepeat() == false){
        on_left_pressed();
    }

    if(event->key() == Qt::Key_D && event->isAutoRepeat() == false){
        on_right_pressed();
    }

    if(event->key() == Qt::Key_S && event->isAutoRepeat() == false){
        on_backward_pressed();
    }



    if(event->key() == Qt::Key_Up && event->isAutoRepeat() == false){
        on_towerUp_pressed();
    }

    if(event->key() == Qt::Key_Left && event->isAutoRepeat() == false){
        on_towerLeft_pressed();
    }

    if(event->key() == Qt::Key_Right && event->isAutoRepeat() == false){
        on_towerRight_pressed();
    }

    if(event->key() == Qt::Key_Down && event->isAutoRepeat() == false){
        on_towerDown_pressed();
    }



    if(event->key() == Qt::Key_Space && event->isAutoRepeat() == false){
        on_shot_clicked();
    }

    if(event->key() == Qt::Key_B && event->isAutoRepeat() == false){
        on_blink_clicked();
    }

    if(event->key() == Qt::Key_C && event->isAutoRepeat() == false){
        on_connect_clicked();
    }

    if(event->key() == Qt::Key_X && event->isAutoRepeat() == false){
        on_stop_clicked();
    }
}

void MainWindow::keyReleaseEvent(QKeyEvent* event){
    if(event->key() == Qt::Key_W && event->isAutoRepeat() == false){
        on_forward_released();
    }

    if(event->key() == Qt::Key_A && event->isAutoRepeat() == false){
        on_left_released();
    }

    if(event->key() == Qt::Key_D && event->isAutoRepeat() == false){
        on_right_released();
    }

    if(event->key() == Qt::Key_S && event->isAutoRepeat() == false){
        on_backward_released();
    }



    if(event->key() == Qt::Key_Up && event->isAutoRepeat() == false){
        on_towerUp_released();
    }

    if(event->key() == Qt::Key_Left && event->isAutoRepeat() == false){
        on_towerLeft_released();
    }

    if(event->key() == Qt::Key_Right && event->isAutoRepeat() == false){
        on_towerRight_released();
    }

    if(event->key() == Qt::Key_Down && event->isAutoRepeat() == false){
        on_towerDown_released();
    }
}


//////////////////////////////////////// GUI ////////////////////////////////////////
////////////////////////////////////////
void MainWindow::on_forward_pressed()
{
//    qDebug() << "W pressed";
//    socket->write("DIR:UP");
    socket->write("COM:1:1");
}

void MainWindow::on_forward_released()
{
//    qDebug() << "W released";
//    socket->write("DIR:STOP");
    socket->write("COM:1:5");
}


////////////////////////////////////////
void MainWindow::on_left_pressed()
{
//    socket->write("DIR:LEFT");
    socket->write("COM:1:2");
}

void MainWindow::on_left_released()
{
//    socket->write("DIR:STOP");
    socket->write("COM:1:5");
}


////////////////////////////////////////
void MainWindow::on_stop_clicked()
{
//    socket->write("DIR:STOP");
    socket->write("COM:1:5");
}


////////////////////////////////////////
void MainWindow::on_right_pressed()
{
//    socket->write("DIR:RIGHT");
    socket->write("COM:1:3");
}

void MainWindow::on_right_released()
{
//    socket->write("DIR:STOP");
    socket->write("COM:1:5");
}


////////////////////////////////////////
void MainWindow::on_backward_pressed()
{
//    socket->write("DIR:BACK");
    socket->write("COM:1:4");
}

void MainWindow::on_backward_released()
{
//    socket->write("DIR:STOP");
    socket->write("COM:1:5");
}


////////////////////////////////////////
void MainWindow::on_speed_valueChanged(int value)
{
//    socket->write(QString("SPEED:").append(QString::number(value)).toStdString().c_str());
    socket->write(QString("COM:2:").append(QString::number(value)).toStdString().c_str());
}


////////////////////////////////////////
void MainWindow::on_color_valueChanged(int value)
{
//    socket->write(QString("COLOR:").append(QString::number(value)).toStdString().c_str());
    socket->write(QString("COM:3:").append(QString::number(value)).toStdString().c_str());
}


////////////////////////////////////////
void MainWindow::on_blink_clicked()
{
//    socket->write("BLINK:TRUE");
    socket->write("COM:4:1");
}


////////////////////////////////////////
void MainWindow::on_sendText_clicked()
{
//    socket->write(QString("TEXT:").append(ui->text->text()).toStdString().c_str());
    socket->write(QString("COM:5:1").append(ui->text->text()).toStdString().c_str());
}


////////////////////////////////////////
void MainWindow::on_clearText_clicked()
{
    ui->text->setText("");
}


////////////////////////////////////////
void MainWindow::on_towerUp_pressed()
{
//    socket->write("TOWER:UP");
    socket->write("COM:6:1");
}

void MainWindow::on_towerUp_released()
{
//    socket->write("TOWER:STOP");
    socket->write("COM:6:5");
}


////////////////////////////////////////
void MainWindow::on_towerLeft_pressed()
{
//    socket->write("TOWER:LEFT");
    socket->write("COM:6:2");
}

void MainWindow::on_towerLeft_released()
{
//    socket->write("TOWER:STOP");
    socket->write("COM:6:5");
}


////////////////////////////////////////
void MainWindow::on_shot_clicked()
{
//    socket->write("SHOT:TRUE");
    socket->write("COM:7:1");
}


////////////////////////////////////////
void MainWindow::on_towerRight_pressed()
{
//    socket->write("TOWER:RIGHT");
    socket->write("COM:6:3");
}

void MainWindow::on_towerRight_released()
{
//    socket->write("TOWER:STOP");
    socket->write("COM:6:5");
}


////////////////////////////////////////
void MainWindow::on_towerDown_pressed()
{
//    socket->write("TOWER:DOWN");
    socket->write("COM:6:4");
}

void MainWindow::on_towerDown_released()
{
//    socket->write("TOWER:STOP");
    socket->write("COM:6:5");
}
