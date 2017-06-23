#ifndef SUNDATA_H
#define SUNDATA_H

#include <QMetaType>
#include <QTime>
#include <QString>

#define SUN_TIME_FORMAT "h:m:s AP"
#define SUN_TIME_SPAN_FORMAT "h:m:s"

class SunData
{
public:
    SunData();
    ~SunData();

    QTime astronomical_twilight_begin;
    QTime astronomical_twilight_end;
    QTime civil_twilight_begin;
    QTime civil_twilight_end;
    QTime day_length;
    QTime nautical_twilight_begin;
    QTime nautical_twilight_end;
    QTime solar_noon;
    QTime sunrise;
    QTime sunset;

    static SunData* fromJson(QString s);
};

Q_DECLARE_METATYPE(SunData)

#endif // SUNDATA_H
