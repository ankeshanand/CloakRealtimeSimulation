#ifndef USER_H
#define USER_H

#include "datapoint.h"

class user
{
private:
    std::vector<dataPoint> myPlaces;
    long int latestTime;
    QString userId;

public:
    user();
    friend class database;
};

#endif // USER_H
