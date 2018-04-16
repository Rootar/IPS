#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include <QTcpSocket>
#include <QtCore>
#include <QDebug>
#include <string>
#include <QString>

#include <QKeyEvent>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private slots:
    void on_forward_released();

    void on_forward_pressed();

    void on_left_pressed();

    void on_left_released();

    void on_stop_clicked();

    void on_right_pressed();

    void on_right_released();

    void on_backward_pressed();

    void on_backward_released();

    void on_connect_clicked();

    void on_speed_valueChanged(int value);

    void on_color_valueChanged(int value);

    void on_blink_clicked();

    void on_sendText_clicked();

    void on_clearText_clicked();

    void on_towerUp_pressed();

    void on_towerUp_released();

    void on_towerLeft_pressed();

    void on_towerLeft_released();

    void on_shot_clicked();

    void on_towerRight_pressed();

    void on_towerRight_released();

    void on_towerDown_pressed();

    void on_towerDown_released();

private:
    Ui::MainWindow *ui;
    QTcpSocket *socket;
    void keyPressEvent(QKeyEvent* event);
    void keyReleaseEvent(QKeyEvent* event);
};

#endif // MAINWINDOW_H
