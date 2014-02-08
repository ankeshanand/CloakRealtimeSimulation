#ifndef DATABASE_H
#define DATABASE_H
#include "datapoint.h"
#include "square.h"
#include "user.h"
//This is the JSON Header
#include "jsoncpp/json.h"

class database
{
private:
    std::vector<dataPoint> points;
    std::vector< std::vector<square> > grid;
    std::vector<square>::iterator it;
    std::map< std::string, dataPoint> userPoints;
    std::vector<user> users;
    double offset_min_la; //offsets of the grid
    double offset_max_la;
    double offset_min_lo;
    double offset_max_lo;
    double range_la;
    double range_lo;
    double range;
    double cell_size; //size of the smallest square
    int cells_x;
    int cells_y;
    int grid_unit; //total squares = grid_unit*grid_unit ideally, but not implemented now
    static database * _instance;//singleton object pointer


public:
    database();
    static database* Instance();
    void generateGrid();
    void computeList(const char *filename);
    void computeOffsets();
    void aggregateForAll();
    void displayCounts();
    void exportCSV();
    void setParents();
    void addNoise();
    friend class square;
    void kAnonymize(int k);
    void setDensities();
    void setParentCount(int param1, int param2, int k);
    void addNoise(double mean, double sigma);
    void restructureCount();
    void exportGeoJSON();
    void newAnonymize(int k);
    void updateParentCounts(int param1, int param2);
    void newParser();
    void exportGeoJSON(std::string filename);
    void exportPointMarkers();
};

#endif // DATABASE_H
