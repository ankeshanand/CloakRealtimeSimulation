#ifndef DATAPOINT_H
#define DATAPOINT_H
#include<QtCore>
#include<vector>
#include "square.h"
class database;

class dataPoint
{
private:
    double la;
    double lo;
    QString user_id;
    QString time;
    QString u_time;

public:
    dataPoint();
    std::vector<square> listContainingSquares();
    dataPoint(QString id, double latitude, double longitude, QString timestamp, QString u_timestamp);

    friend class database;
};

#endif // DATAPOINT_H
