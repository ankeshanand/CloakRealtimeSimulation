#include <QtGui/QApplication>
#include "mainwindow.h"
#include<jsoncpp/json.h>
#include<iostream>
#include<fstream>
#include"database.h"

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    MainWindow w;
    database *location_data;
    location_data  = database::Instance();
    const char *filename= "location_data.json";
    //location_data->computeList(filename);
//    location_data->computeOffsets();
//    location_data->generateGrid();
//    location_data->aggregateForAll();
//    location_data->setParents();
//    //location_data->setDensities();
//    location_data->newAnonymize(10);
//    location_data->displayCounts();
//    location_data->exportCSV();
//    location_data->exportGeoJSON("geoData2.js");
//    location_data->addNoise(0,20);
//    location_data->exportGeoJSON("geoData_noise.js");
    location_data->newParser();
 //  location_data->exportPointMarkers();



    w.show();
    return a.exec();
}
