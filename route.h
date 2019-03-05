#ifndef ROUTE_H
#define ROUTE_H

/*
 * Autor:  Killer Lorenz
 * Klasse: 5BHIF
 * Datum:  21.02.2019
 * File:   route.h
 */

#include "airport.h"

class Route {
public:
    int airline;
    int airport1;
    int airport2;

    int getOtherAirportID(int id) const{
        return (id == airport1) ? airport2 : airport1;
    }
};

#endif // ROUTE_H
