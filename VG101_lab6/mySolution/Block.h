#ifndef BLOCK_H
#define BLOCK_H
#include "Vector2D.h"

enum BlockStatus
{
    Empty,
    WithBullet,
    WithTank
};

class Block
{
private:
    Vector2D<int> position;
    BlockStatus status;

public:
    Block(int x = 0, int y = 0);

    void switchStatusTo(BlockStatus newStatus);
};

Block::Block(int x, int y)
{
    Vector2D<int> position_(x, y);
    position = position_;

    status = Empty;
}

void Block::switchStatusTo(BlockStatus newStatus)
{
    status = newStatus;
}

#endif