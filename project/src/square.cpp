#include "square.h"
#include "database.h"
square::square()
{
    count = 0;
    id=setId();
    parentId = 0;
    parentParam1 = -1;
    parentParam2 = -1;
    isSet = 0;
    density = 0;
}

void square::computeDensity()
{
}

int square::id_counter = 0;

int square::setId()
{
    return ++id_counter;
}

void square::aggregate()
{
}

void square::updateCount(long new_count)
{
}

