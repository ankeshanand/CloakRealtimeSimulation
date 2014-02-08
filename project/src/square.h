#ifndef SQUARE_H
#define SQUARE_H
#include<algorithm>
#include<vector>

class square
{
private:
    int size;
    double offset_x;
    double offset_y;
    int row;
    int column;
    int scale;
    long int count;
    static int id_counter;
    int id;
    int parentId;
    int parentParam1;
    int parentParam2;
    int isSet;
    double density;
    double orgDensity;
    double noiseDensity;
    std::vector< std::pair<int,int> > children;


public:
    square();
    void computeDensity();
    void aggregate();
    void updateCount(long int new_count);

    friend class database;
    int setId();
};

#endif // SQUARE_H
