#include "Vector2D.h"
#include "Direction.h"
#include "Bullet.h"
#ifndef TANK_H
#define TANK_H

class Tank
{
private:
    Point position;
    int lifePoints;
    Direction direction;
    const int TANK_SPEED;

public:
    Tank(Point position_, Direction dirction_);
    void move();
    Point getPosition();
    void shoot(vector<Bullet> &bullets);
    ~Tank();
};

#endif