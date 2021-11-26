#include "Vector2D.h"
#ifndef RECTANGLE_H
#define RECTANGLE_H

class Rectangle
{
private:
    Point leftTop;
    Point rightBottom;

public:
    Rectangle();
    ~Rectangle();
    Point getCenter();
    int getArea();
}

#endif