#include "Vector2D.h"
#ifndef DIRECTION_H
#define DIRECTION_H

enum Direction
{
    EAST,
    NORTH,
    WEST,
    SOUTH
};

Point convertDirToPoint(Direction dir)
{
    Point point;
    switch (dir)
    {
    case EAST:
        point = {1, 0};
        break;
    case NORTH:
        point = {0, -1};
        break;
    case WEST:
        point = {-1, 0};
        break;
    case SOUTH:
        point = {0, 1};
        break;
    default:
        break;
    }
    return point;
}

Direction turnLeft(Direction dir)
{
    switch (dir)
    {
    case EAST:
        return NORTH;
    case NORTH:
        return WEST;
    case WEST:
        return SOUTH;
    case SOUTH:
        return EAST;
    default:
        break;
    }
}

Direction turnRight(Direction dir)
{
    switch (dir)
    {
    case EAST:
        return SOUTH;
    case NORTH:
        return EAST;
    case WEST:
        return NORTH;
    case SOUTH:
        return WEST;
    default:
        break;
    }
}

#endif