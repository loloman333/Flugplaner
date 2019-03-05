#ifndef DRAWABLEMAPWIDGET_H
#define DRAWABLEMAPWIDGET_H

/*
 * Autor:  Killer Lorenz
 * Klasse: 5BHIF
 * Datum:  21.02.2019
 * File:   drawablemapwidget.h
 */

#include <QWidget>
#include "dbmanager.h"
#include <QApplication>
#include "airport.h"

class DrawableMapWidget : public QWidget
{
    Q_OBJECT
public:
    explicit DrawableMapWidget(QWidget *parent = nullptr);

    void paintEvent(QPaintEvent* e);
    std::tuple<double, double> latLonToImg(double lat, double lon);
    std::tuple<double, double> latLonToImg(std::tuple<double, double, double> inp);

    QList<Airport> airports;

    void connectTheDots(QList<QList<Airport>> routes);

    QPoint latLonToPoint(double lat, double lon);

    void resetPic();
signals:

public slots:

private:
    QPixmap pic;

    void connectAirports(Airport from, Airport to, QPainter &painter);

};

#endif // DRAWABLEMAPWIDGET_H
