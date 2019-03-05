/*
 * Autor:  Killer Lorenz
 * Klasse: 5BHIF
 * Datum:  21.02.2019
 * File:   mainwindow.cpp
 */

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QMessageBox>

QList<Airport> MainWindow::getPath(Airport end){
    QList<Airport> path;   
    Airport a = end;

    path.push_front(a);

    while (a.parent != nullptr){
        a = *a.parent;
        path.push_front(a);
    }
    return path;
}

QList<QList<Airport>> MainWindow::findPaths(Airport start, Airport end){

    QList<QList<Airport>> paths;

    QList<QList<Airport>> level;
    level.push_back(QList<Airport>{start});

    bool nextLevel{true};
    int i = 0;

    QList<int> forbiddenAriports;

    while (nextLevel){

        if(level[i].length() == 0){
            QMessageBox msgBox;

            msgBox.setIcon(QMessageBox::Warning);
            msgBox.setText("Keine Pfade gefunden!");
            msgBox.setStandardButtons(QMessageBox::Ok);

            msgBox.exec();
            break;
        }

        level.push_back(QList<Airport>{});

        for (Airport a : level[i]){
            forbiddenAriports.push_back(a.id);
        }

        for (int j{0}; j < level[i].length(); j++){

            Airport& a = level[i][j];       //Maybe change that to use it everytime

            if (a.id == end.id){

                nextLevel = false;
                paths.push_back(getPath(a));
            } else if (nextLevel) {
                QList<Airport> neighbors = db.getAdjecantAirports(a.id);

                for (int l{0}; l < neighbors.length(); l++){
                    Airport& neighbor = neighbors[l];

                    if (! forbiddenAriports.contains(neighbor.id)){
                        neighbor.parent = &a;

                        level[i + 1].push_back(std::move(neighbor));
                    }

                }
            }
        }
        i++;
    }
    return paths;
}

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow) {

    ui->setupUi(this);

    QList<Airport> airports = db.getAllAirports();
    QList<Airline> airlines = db.getAllAirlines();

    ui->map->airports = airports;
    ui->map->resetPic();

    for (int i{0}; i < airports.length(); i++){
        Airport a = airports[i];

        ui->comboBoxStart->addItem(
            (a.iata + " - " + a.name).trimmed(),
            a.id
        );
        ui->comboBoxEnd->addItem(
            (a.iata + " - " + a.name).trimmed(),
            a.id
        );
    }

    for (int i{0}; i < airlines.length(); i++){
        Airline a = airlines[i];

        ui->comboBoxAirline->addItem(
            a.name, a.id
        );
    }
}

MainWindow::~MainWindow() {
    delete ui;
}

void MainWindow::on_buttonSearch_clicked() {

    int startAirportId{
        ui->comboBoxStart->currentData().toInt()
    };
    int endAirportId{
        ui->comboBoxEnd->currentData().toInt()
    };
    int favoredAirlineId{
        ui->comboBoxAirline->currentData().toInt()
    };

    Airport startAirport{db.getAirport(startAirportId)};
    Airport endAirport{db.getAirport(endAirportId)};
    Airline favoredAirline{db.getAirline(favoredAirlineId)};

    QList<QList<Airport>> paths = findPaths(startAirport, endAirport);

    for (int i{0}; i < paths.length(); i++){
        QList<Airport>& path = paths[i];

        for (int j{1}; j < path.length(); j++){
                path[j].color = db.getColorOfConnection(path[j - 1].id, path[j].id, favoredAirlineId);
        }
    }

    ui->map->connectTheDots(paths);

    ui->listResults->clear();

    for (auto path : paths) {
        QString s{""};
        for (size_t i{0}; i < path.length() - 1; i++) {
            s += path[i].iata + " -> ";
        }
        s += path[path.length() - 1].iata;

        ui->listResults->addItem(s);
    }
}


void MainWindow::on_actionAbout_triggered()
{
    QMessageBox msgBox;

    msgBox.setIcon(QMessageBox::Information);
    msgBox.setText("Autor: Lorenz Killer <br> Klasse: 5BHIF <br> Datum: 20.02.2019");
    msgBox.setStandardButtons(QMessageBox::Ok);

    msgBox.exec();
}
