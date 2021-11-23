#include <iostream>
#include "hand.h"

using namespace std;

int getNormalCount(const Spot &spot);

Hand::Hand() : curValue({0, false}) {}

void Hand::discardAll()
{
    curValue = {0, false};
}

void Hand::addCard(Card c)
{
    if (!curValue.soft)
    {
        if (c.spot != ACE)
        {
            curValue.count += getNormalCount(c.spot);
            return;
        }
        if (curValue.count <= 10)
        {
            curValue.count += 11;
            curValue.soft = true;
        }
        else
            curValue.count += 1;
    }
    else
    {
        if (curValue.count + getNormalCount(c.spot) > 21)
        {
            curValue.count = curValue.count + getNormalCount(c.spot) - 10;
            curValue.soft = false;
        }
        else
            curValue.count += getNormalCount(c.spot);
    }
}

HandValue Hand::handValue() const
{
    return curValue;
}

int getNormalCount(const Spot &spot)
{
    if (spot <= 8)
        return spot + 2;
    if (spot <= 11)
        return 10;
    return 1;
}