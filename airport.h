#ifndef AIRPORT_H
#define AIRPORT_H

/*
 * Autor:  Killer Lorenz
 * Klasse: 5BHIF
 * Datum:  21.02.2019
 * File:   airport.h
 */

#include <QString>

class Airport {
public:
    int id;
    float latitude;
    float longitude;
    QString name;
    QString iata;

    int color;

    QList<Airport>* children;
    Airport* parent = nullptr;
};


#endif // AIRPORT_H

/*#ifndef ALLIANCE_H
#define ALLIANCE_H

#include <QString>

class Alliance {
public:
    int id;
    QString name;
};

#endif // ALLIANCE_H
*/
