#include "Block.h"
#include "Rectangle.h"
#ifndef MAP_H
#define MAP_H

class Map
{
private:
    const int MAP_SIZE = 20;
    Block map[MAP_SIZE][MAP_SIZE];
    Rectangle validRegion;

public:
    Map();
    ~Map();
}

#endif