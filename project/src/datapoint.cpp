#include "datapoint.h"

dataPoint::dataPoint(QString id,double latitude, double longitude,QString timestamp, QString u_timestamp)
{
    user_id=id;
    la=latitude;
    lo=longitude;
    time=timestamp;
    u_time=u_timestamp;
}

dataPoint::dataPoint()
{

}

std::vector<square> dataPoint::listContainingSquares()
{

}
