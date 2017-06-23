#include <QPaintEvent>
#include <QPainter>
#include <QColor>
#include <math.h>

#include "sundataview.h"

#define SUN_RADIUS 10
#define PI 3.14159265

SunDataView::SunDataView(QWidget *parent) : QWidget(parent)
{
}

void SunDataView::paintEvent(QPaintEvent* paintEvent)
{
    QPainter painter(this);

    if (current < sunrise || current > sunrise + day_length)
    {
        // night
        painter.fillRect(paintEvent->rect(), Qt::black);
    }
    else
    {
        painter.fillRect(paintEvent->rect(), QColor(127, 127, 255));

        double width = (double)paintEvent->rect().width();
        double height = (double)paintEvent->rect().height();
        double currentPos = (double)(current - sunrise)/(double)day_length;

        double sunX =  currentPos * width;
        double sunY = height - sin(currentPos * PI) * (height - SUN_RADIUS);

        painter.setBrush(Qt::yellow);
        painter.setPen(Qt::red);
        painter.drawEllipse(QRect(sunX - SUN_RADIUS, sunY - SUN_RADIUS, 2 * SUN_RADIUS, 2 * SUN_RADIUS));
    }
}
