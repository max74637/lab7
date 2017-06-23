#include <QTime>

#include "dialog2.h"
#include "ui_dialog2.h"

#include "sundataview.h"

Dialog2::Dialog2(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog2)
{
    ui->setupUi(this);
}

Dialog2::~Dialog2()
{
    delete ui;
}

void Dialog2::setSunData(SunData* sunData)
{
    QTime currentTime = QDateTime::currentDateTimeUtc().time();
    int sunrise = QTime(0, 0, 0).secsTo(sunData->sunrise);
    int day_length  = QTime(0, 0, 0).secsTo(sunData->day_length);
    int current  = QTime(0, 0, 0).secsTo(currentTime);
    int period = 24 * 60 * 60;

    bool isDay = current > sunrise && current < sunrise + day_length;
    if (!isDay && (current + period > sunrise && current  + period < sunrise + day_length)) {
        current += period;
        isDay = true;
    }

    int beforeSunset = isDay ? sunrise + day_length - current : -1;

    QLabel* label = findChild<QLabel*>("labelSunrise");
    label->setText("Sunrise: " + sunData->sunrise.toString(SUN_TIME_FORMAT));

    label = findChild<QLabel*>("labelSunset");
    label->setText("Sunset: " + sunData->sunset.toString(SUN_TIME_FORMAT));

    label = findChild<QLabel*>("labelCurrentTime");
    label->setText("Current Time: " + currentTime.toString(SUN_TIME_FORMAT));

    QString sSecsTo = isDay ?
                QTime::fromMSecsSinceStartOfDay(beforeSunset * 1000).toString(SUN_TIME_SPAN_FORMAT) :
                " - night -";
    label = findChild<QLabel*>("labelBeforeSunset");
    label->setText("Before Sunset: " + sSecsTo);

    SunDataView* sunDataView = findChild<SunDataView*>("sunDataView");
    sunDataView->sunrise = sunrise;
    sunDataView->day_length  = day_length;
    sunDataView->current  = current;
}
