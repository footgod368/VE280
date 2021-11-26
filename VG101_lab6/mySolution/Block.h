#include "Vector2D.h"

#ifndef BLOCK_H
#define BLOCK_H

enum BlockStatus
{
    Empty,
    WithBullet,
    WithTank
};

class Block
{
private:
    Point position;
    BlockStatus status;

public:
    Block(int x = 0, int y = 0);
    void switchStatusTo(BlockStatus newStatus);
};

#endif