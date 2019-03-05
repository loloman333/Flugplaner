#ifndef MAINWINDOW_H
#define MAINWINDOW_H

/*
 * Autor:  Killer Lorenz
 * Klasse: 5BHIF
 * Datum:  21.02.2019
 * File:   mainwindow.h
 */

#include <QMainWindow>
#include <QFile>
#include <QFileInfo>
#include <QDebug>
#include <QSet>
#include <QMutableSetIterator>

#include "airport.h"
#include "airline.h"
//#include "alliance.h"
#include "route.h"
#include "dbmanager.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    DBManager db;

private slots:
    void on_buttonSearch_clicked();

    void on_actionAbout_triggered();

private:
    Ui::MainWindow *ui;

    QList<Airport> getPath(Airport);
    QList<QList<Airport>> findPaths(Airport, Airport);

};

#endif // MAINWINDOW_H
