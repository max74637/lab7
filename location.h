#ifndef LOCATION_H
#define LOCATION_H

#include <QMetaType>
#include <QString>

class Location
{
public:
    Location();
    Location(const QString& name, double latitude, double longitude);
    ~Location();

    QString getName();
    double getLatitude();
    double getLongitude();

private:
    QString _name;
    double _latitude;
    double _longitude;
};

Q_DECLARE_METATYPE(Location)

#endif // LOCATION_H
