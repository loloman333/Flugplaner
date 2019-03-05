#include "airport.h"

Airport::Airport() {
public:
    int id;
    float latitude;
    float longitude;
    QString name;
    QString iata;
}

QList<Airport> Airport::getChildren() const
{
    return children;
}

void Airport::setChildren(const QList<Airport> &value)
{
    children = value;
}
