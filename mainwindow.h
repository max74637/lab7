#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QComboBox>
#include <QVector>
#include <QNetworkAccessManager>
#include <QNetworkReply>

#include "location.h"

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
    void on_pushButton_1_clicked();
    void on_pushButton_2_clicked();
    void on_pushButton_3_clicked();
    void on_network_reply_finished_2();
    void on_network_reply_finished_3();

private:
    QComboBox* comboBox;
    QVector<Location> locations;
    QNetworkAccessManager networkAccessManager;
    QNetworkReply* networkReply;

private:
    Ui::MainWindow *ui;
};

#endif // MAINWINDOW_H
