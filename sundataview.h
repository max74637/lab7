#ifndef SUNDATAVIEW_H
#define SUNDATAVIEW_H

#include <QWidget>

class SunDataView : public QWidget
{
    Q_OBJECT
public:
    explicit SunDataView(QWidget *parent = 0);

    int sunrise;
    int day_length;
    int current;

protected:
    virtual void paintEvent(QPaintEvent* paintEvent);

signals:

public slots:
};

#endif // SUNDATAVIEW_H
