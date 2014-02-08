#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include <QtWebKit>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    ui->webView->load(QUrl("http://localhost/CloakSimulation/map_visualization.html"));
    ui->webView->show();
    ui->webView_2->load(QUrl("http://localhost/CloakSimulation/map_visualization_noise.html"));
    ui->webView_2->show();
    ui->webView_3->load(QUrl("http://localhost/CloakSimulation/differenceChart.html"));
    ui->webView_3->show();

}

MainWindow::~MainWindow()
{
    delete ui;
}



void MainWindow::on_horizontalSlider_sliderMoved(int position)
{
//    std::cout << position <<"\n";
//    database *location_data;
//    location_data = database::Instance();
//    location_data->newAnonymize(position);
//    location_data->exportCSV();
//    location_data->exportGeoJSON("geoData2.js");
//    ui->webView->load(QUrl("http://localhost/CloakSimulation/map_visualization.html"));
//    location_data->addNoise(0,20);
//    ui->webView->load(QUrl("http://localhost/CloakSimulation/map_visualization_noise.html"));
//    ui->webView_3->load(QUrl("http://localhost/CloakSimulation/differenceChart.html"));
}

void MainWindow::on_horizontalSlider_actionTriggered(int action)
{

}

void MainWindow::on_horizontalSlider_valueChanged(int value)
{
//    std::cout<<"*************** " <<value << "**********" <<"\n";
//    database *location_data;
//    location_data = database::Instance();
//    location_data->setDensities();
//    location_data->newAnonymize(value);
//    location_data->exportCSV();
//    ui->webView->load(QUrl("http://localhost/CloakSimulation/visualization.html"));

    database *location_data;
    location_data = database::Instance();
    location_data->newAnonymize(value);
    location_data->exportCSV();
    location_data->exportGeoJSON("geoData2.js");
    ui->webView->load(QUrl("http://localhost/CloakSimulation/map_visualization.html"));
    location_data->addNoise(0,20);
    location_data->exportGeoJSON("geoData_noise.js");
    ui->webView_2->load(QUrl("http://localhost/CloakSimulation/map_visualization_noise.html"));
    ui->webView_3->load(QUrl("http://localhost/CloakSimulation/differenceChart.html"));

}

void MainWindow::on_horizontalSlider_2_valueChanged(int value)
{

}
