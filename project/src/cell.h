#ifndef CELL_H
#define CELL_H

class cell
{
private:
    int size;
    double offset_x;
    double offset_y;
    int scale;
    long int count;

public:
    cell();
    void aggregate();
    void updateCount(long int new_count);
};

#endif // CELL_H
