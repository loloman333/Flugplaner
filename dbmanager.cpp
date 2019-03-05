/*
 * Autor:  Killer Lorenz
 * Klasse: 5BHIF
 * Datum:  21.02.2019
 * File:   dbmanager.cpp
 */

#include "dbmanager.h"

DBManager::DBManager() {

    QString path{
       QFileInfo(
            QCoreApplication::applicationDirPath()
        ).filePath() + "/Airline.db"
    };

    QFile::copy(":/res/AirlineRoutes.db" , path);

    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName(path);

    if (!m_db.open()) {
        qDebug() << "Error: connection with database fail";
    } else {
        qDebug() << "Database: connection ok";

        loadAllAirlines();
        loadAllAirports();
        loadAllRoutes();
    }
}

void DBManager::loadAllAirlines(){
    QSqlQuery query(m_db);

    query.prepare("select * from  Airline");
    query.exec();

    int idId = query.record().indexOf("id");
    int idName = query.record().indexOf("name");
    int idAlliance = query.record().indexOf("alliance");

    while (query.next()) {
        Airline a;
        a.id = query.value(idId).toInt();
        a.name = query.value(idName).toString();
        a.alliance = query.value(idAlliance).toInt();

        airlines.push_back(a);
    }
}

void DBManager::loadAllAirports(){
    QSqlQuery query(m_db);

    query.prepare("select * from  Airport");
    query.exec();

    int idId = query.record().indexOf("id");
    int idLatitude = query.record().indexOf("latitude");
    int idLongitude = query.record().indexOf("longitude");
    int idIATA = query.record().indexOf("iata");
    int idName = query.record().indexOf("name");

    while (query.next()) {
        Airport a;
        a.id = query.value(idId).toInt();
        a.latitude = query.value(idLatitude).toFloat();
        a.longitude = query.value(idLongitude).toFloat();
        a.iata = query.value(idIATA).toString();
        a.name = query.value(idName).toString();

        airports.push_back(a);
    }

    airportCount = airports.length();
}

void DBManager::loadAllRoutes(){
    QSqlQuery query(m_db);

    query.prepare("select * from  Route");
    query.exec();

    int idAirport1 = query.record().indexOf("airport1");
    int idAirport2 = query.record().indexOf("airport2");

    connections.reserve(airportCount);

    for (int i{0}; i < airportCount; i++){
        connections.push_back(QList<int>{});
    }

    while (query.next()) {

        int airport1 = query.value(idAirport1).toInt();
        int airport2 = query.value(idAirport2).toInt();

        if (! connections[airport1].contains(airport2)){
            connections[airport1].push_back(airport2);
        }
    }
}

Airport DBManager::getAirport(int id){
    return airports[id - 1];
}

Airline DBManager::getAirline(int id){
    return airlines[id - 1];
}

QList<Airport> DBManager::getAdjecantAirports(int airportID){

    QList<int> idList = connections[airportID];

    QList<Airport> airportList;

    for (auto i : idList){
        Airport a = getAirport(i);

        airportList.push_back(a);
    }

    return airportList;
}

QList<Airline> DBManager::getAllAirlines(){
    return airlines;
}

QList<Airport> DBManager::getAllAirports(){
    return airports;
}

int DBManager::getColorOfConnection(int a1id, int a2id, int airline){
    QSqlQuery query(m_db);

    query.prepare("select * from  Route where airport1 = :a1id and airport2 = :a2id");

    query.bindValue(":a1id", a1id);
    query.bindValue(":a2id", a2id);

    query.exec();

    int idAirline = query.record().indexOf("airline");
    int color = 1;

    while (query.next()) {
        int al = query.value(idAirline).toInt();

        if ( al == airline) {
            color = 3;
            break;
        } else if ( getAirline(al).alliance == getAirline(airline).alliance) {
            color = 2;
        }
    }
    return color;
}
// 1 -> gray(other), 2 -> blue (alliance), 3 -> red (airline);
