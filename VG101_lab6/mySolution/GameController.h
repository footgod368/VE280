#include <vector>
#include "Block.h"
#include "Tank.h"
#include "Bullet.h"
#include "Map.h"

#ifndef GAME_CONTROLLER_H
#define GAME_CONTROLLER_H

class GameController
{
private:
    Tank *tank_1;
    Tank *tank_2;
    vector<Bullet> bullets;
    Map *map;

public:
    Game();
    ~Game();
}

#endif