#ifndef DBMANAGER_H
#define DBMANAGER_H

/*
 * Autor:  Killer Lorenz
 * Klasse: 5BHIF
 * Datum:  21.02.2019
 * File:   dbmanager.h
 */

#include <QSqlDatabase>
#include <QString>
#include <QDebug>
#include <QCoreApplication>
#include <QFileInfo>
#include <QSqlQuery>
#include <QSqlRecord>

#include "airline.h"
#include "airport.h"
//#include "alliance.h"
#include "route.h"

class DBManager : QObject{
public:
    DBManager();

    QList<Airport>  getAllAirports();
    QList<Airline>  getAllAirlines();

    Airport         getAirport(int);
    Airline          getAirline(int);

    QList<Airport>  getAdjecantAirports(int);

    int getColorOfConnection(int, int, int);
private:
    QSqlDatabase    m_db;

    void  loadAllAirports();
    void  loadAllAirlines();
    void  loadAllRoutes();

    int airportCount;

    QList<Airport>    airports;
    QList<Airline>    airlines;
    QList<QList<int>> connections;
};

#endif // DBMANAGER_H
