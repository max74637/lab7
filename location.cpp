#include "location.h"

Location::Location()
{

}

Location::Location(const QString& name, double latitude, double longitude)
{
    _name = name;
    _latitude = latitude;
    _longitude = longitude;
}

Location::~Location()
{
}

QString Location::getName()
{
    return _name;
}

double Location::getLatitude()
{
    return _latitude;
}

double Location::getLongitude()
{
    return _longitude;
}
