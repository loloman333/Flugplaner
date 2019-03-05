/*
 * Autor:  Killer Lorenz
 * Klasse: 5BHIF
 * Datum:  21.02.2019
 * File:   drawablemapwidget.cpp
 */

#include "drawablemapwidget.h"

#include "mainwindow.h"
#include <algorithm>

#include <QStringList>
#include <QPainter>
#include <QApplication>

DrawableMapWidget::DrawableMapWidget(QWidget *parent) : QWidget(parent) {

}

void DrawableMapWidget::paintEvent(QPaintEvent*)
{
    QPainter painter{this};
    painter.drawPixmap(0, 0, pic);
}

QPoint DrawableMapWidget::latLonToPoint(double lat, double lon)
{
    return QPoint((lon + 180.0) * 3.0,
                  (lat - 90.0) * -3.0);
}

void DrawableMapWidget::connectAirports(Airport fromAP, Airport toAP, QPainter &painter)
{
    auto directDistance = abs(fromAP.longitude - toAP.longitude);
    auto roundDistance = 360.0 - directDistance;

    auto fromPoint = latLonToPoint(fromAP.latitude, fromAP.longitude);
    auto toPoint = latLonToPoint(toAP.latitude, toAP.longitude);

    if (directDistance < roundDistance)
    {
       painter.drawLine(fromPoint, toPoint);
    }
    else
    {
       auto leftSide = latLonToPoint((fromAP.latitude + toAP.latitude) / 2, -180.0);
       auto rightSide = latLonToPoint((fromAP.latitude + toAP.latitude) / 2, 180.0);

       if (fromAP.longitude > 0)
       {
           painter.drawLine(fromPoint, rightSide);
           painter.drawLine(leftSide, toPoint);
       }
       else
       {
           painter.drawLine(fromPoint, leftSide);
           painter.drawLine(rightSide, toPoint);
       }
    }

    QPen greenPen{Qt::green, 4};
    painter.setPen(greenPen);

    painter.drawPoint(fromPoint);
    painter.drawPoint(toPoint);

    QPen blackPen{Qt::black, 3};
    painter.setPen(blackPen);

    fromPoint.setY(fromPoint.y() + 15);
    fromPoint.setX(fromPoint.x() + 10);
    toPoint.setY(toPoint.y() + 15);
    toPoint.setX(toPoint.x() + 10);

    painter.drawText(fromPoint, fromAP.iata);
    painter.drawText(toPoint, toAP.iata);
}

void DrawableMapWidget::connectTheDots(QList<QList<Airport>> paths)
{
    resetPic();

    QPainter painter{&pic};
    QPen selected_flight{Qt::red, 2};
    QPen alliance_flight{Qt::blue, 2};
    QPen every_flight{Qt::gray, 2};

    for (auto path : paths) {
        for (int i{0}; i < path.length() - 1; i++) {
            Airport fromAP = path[i];
            Airport toAP = path[i + 1];

            qDebug() << toAP.iata;
            qDebug() << toAP.color;

            if (toAP.color == 3){
                painter.setPen(selected_flight);
            } else if (toAP.color == 2){
                painter.setPen(alliance_flight);
            } else {
                painter.setPen(every_flight);
            }

            connectAirports(fromAP, toAP, painter);
        }
    }

    update();
}

void DrawableMapWidget::resetPic()
{
    QPixmap l_pic{1080, 540};
    QPainter painter(&l_pic);
    QPixmap map(":/res/Earthmap.jpg");
    map = map.scaled(1080, 540 , Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, map);
    /*
    painter.setPen(QPen{QBrush{QColor{0, 255, 0, 200}}, 3});


    for (auto airport : airports) {
        painter.drawPoint(latLonToPoint(airport.latitude, airport.longitude));
    }*/

    pic = l_pic;
}




