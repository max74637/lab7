#include <QDesktopWidget>

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include "utils.h"
#include "sundata.h"
#include "dialog1.h"
#include "dialog2.h"

#define URL_1 "https://api.github.com/"
#define URL_2 "https://api.sunrise-sunset.org/"
#define URL_2_FORMAT "https://api.sunrise-sunset.org/json?lat=%f&lng=%f"
#define SUN_DATA_FORMAT "%s sun data"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // center to screen
    setGeometry(
        QStyle::alignedRect(
            Qt::LeftToRight,
            Qt::AlignCenter,
            size(),
            QApplication::desktop()->availableGeometry()
        )
    );

    QLabel* label = findChild<QLabel*>("label_1");
    label->setText("1. " URL_1);

    label = findChild<QLabel*>("label_2");
    label->setText("2. " URL_2);

    label = findChild<QLabel*>("label_3");
    label->setText("3. " URL_2);

    locations.push_back(Location("New York",      40.7127,   -74.0059));
    locations.push_back(Location("Buenos Aires", -34.603333, -58.381667));
    locations.push_back(Location("Paris",         48.8567,     2.3508));
    locations.push_back(Location("Kiev",          50.45,      30.523333));
    locations.push_back(Location("Beijing",       39.916667, 116.383333));
    locations.push_back(Location("Tokyo",         35.683333, 139.683333));
    locations.push_back(Location("Sydney",       -33.865,    151.209444));

    comboBox = findChild<QComboBox*>("comboBox");
    for (int n = 0; n < locations.size(); n++)
        comboBox->addItem(locations[n].getName(), QVariant::fromValue(locations[n]));
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::on_pushButton_1_clicked()
{
    QByteArray result = WebGet(URL_1);
    QString sResult = TestJsonResult(result);
    Dialog1 dlg;
    dlg.setWindowTitle(URL_1);
    dlg.setResultText(sResult);
    dlg.exec();
}

void MainWindow::on_pushButton_2_clicked()
{  
    Location location = locations[0];
    QString url = QString().sprintf(URL_2_FORMAT, location.getLatitude(), location.getLongitude());
    networkReply = networkAccessManager.get(QNetworkRequest(url));
    connect(networkReply, &QNetworkReply::finished, this, &MainWindow::on_network_reply_finished_2);
}

void MainWindow::on_pushButton_3_clicked()
{
    Location location = comboBox->currentData().value<Location>();
    QString url = QString().sprintf(URL_2_FORMAT, location.getLatitude(), location.getLongitude());
    networkReply = networkAccessManager.get(QNetworkRequest(url));
    connect(networkReply, &QNetworkReply::finished, this, &MainWindow::on_network_reply_finished_3);
}

void MainWindow::on_network_reply_finished_2()
{
    Location location = locations[0];
    QString title = QString().sprintf(URL_2_FORMAT, location.getLatitude(), location.getLongitude());

    QByteArray result = networkReply->readAll();
    QString sResult = TestJsonResult(result);
    Dialog1 dlg;
    dlg.setWindowTitle(title);
    dlg.setResultText(sResult);
    dlg.exec();

    networkReply->deleteLater();
    networkReply = Q_NULLPTR;
}

void MainWindow::on_network_reply_finished_3()
{
    Location location = comboBox->currentData().value<Location>();
    QString title = QString().sprintf(SUN_DATA_FORMAT, location.getName().toLocal8Bit().data());

    QByteArray result = networkReply->readAll();
    SunData* sunData = SunData::fromJson(result);
    if (sunData != Q_NULLPTR)
    {
        Dialog2 dlg;
        dlg.setWindowTitle(title);
        dlg.setSunData(sunData);
        dlg.exec();
    }

    networkReply->deleteLater();
    networkReply = Q_NULLPTR;
}
