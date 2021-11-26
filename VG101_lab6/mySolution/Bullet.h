#include "Direction.h"
#ifndef BULLET_H
#define BULLET_H

class Bullet
{
private:
    Point position;
    Direction direction;
    const int BULLET_SPEED;

public:
    Bullet();
    ~Bullet();
}

#endif