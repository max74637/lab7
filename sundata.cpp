#include <QJsonDocument>
#include <QJsonObject>
#include <QString>

#include "sundata.h"

SunData::SunData()
{
}

SunData::~SunData()
{
}

SunData* SunData::fromJson(QString s)
{
    QJsonDocument doc = QJsonDocument::fromJson(s.toUtf8());
    if (doc.isNull())
        return Q_NULLPTR;

    QJsonObject obj = doc.object();
    if (obj.isEmpty())
        return Q_NULLPTR;

    QJsonObject results = obj["results"].toObject();
    if (results.isEmpty())
        return Q_NULLPTR;

    QString value = results["astronomical_twilight_begin"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime astronomical_twilight_begin = QTime::fromString(value, SUN_TIME_FORMAT);
    if (!astronomical_twilight_begin.isValid())
        return Q_NULLPTR;

    value = results["astronomical_twilight_end"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime astronomical_twilight_end = QTime::fromString(value, SUN_TIME_FORMAT);
    if (!astronomical_twilight_end.isValid())
        return Q_NULLPTR;

    value = results["civil_twilight_begin"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime civil_twilight_begin = QTime::fromString(value, SUN_TIME_FORMAT);
    if (!civil_twilight_begin.isValid())
        return Q_NULLPTR;

    value = results["civil_twilight_end"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime civil_twilight_end = QTime::fromString(value, SUN_TIME_FORMAT);
    if (!civil_twilight_end.isValid())
        return Q_NULLPTR;

    value = results["day_length"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime day_length = QTime::fromString(value, SUN_TIME_SPAN_FORMAT);
    if (!day_length.isValid())
        return Q_NULLPTR;

    value = results["nautical_twilight_begin"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime nautical_twilight_begin = QTime::fromString(value, SUN_TIME_FORMAT);
    if (!nautical_twilight_begin.isValid())
        return Q_NULLPTR;

    value = results["nautical_twilight_end"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime nautical_twilight_end = QTime::fromString(value, SUN_TIME_FORMAT);
    if (!nautical_twilight_end.isValid())
        return Q_NULLPTR;

    value = results["solar_noon"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime solar_noon = QTime::fromString(value, SUN_TIME_FORMAT);
    if (!solar_noon.isValid())
        return Q_NULLPTR;

    value = results["sunrise"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime sunrise = QTime::fromString(value, SUN_TIME_FORMAT);
    if (!sunrise.isValid())
        return Q_NULLPTR;

    value = results["sunset"].toString();
    if (value.isEmpty())
        return Q_NULLPTR;
    QTime sunset = QTime::fromString(value, SUN_TIME_FORMAT);
    if (!sunset.isValid())
        return Q_NULLPTR;

    SunData* sunData = new SunData();
    sunData->astronomical_twilight_begin = astronomical_twilight_begin;
    sunData->astronomical_twilight_end   = astronomical_twilight_end;
    sunData->civil_twilight_begin        = civil_twilight_begin;
    sunData->civil_twilight_end          = civil_twilight_end;
    sunData->day_length                  = day_length;
    sunData->nautical_twilight_begin     = nautical_twilight_begin;
    sunData->nautical_twilight_end       = nautical_twilight_end;
    sunData->solar_noon                  = solar_noon;
    sunData->sunrise                     = sunrise;
    sunData->sunset                      = sunset;

    return sunData;
}
