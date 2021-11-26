#include "Block.h"

Block::Block(int x, int y)
{
    Point position_(x, y);
    position = position_;

    status = Empty;
}

void Block::switchStatusTo(BlockStatus newStatus)
{
    status = newStatus;
}