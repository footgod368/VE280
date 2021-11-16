#include <iostream>
#include <cassert>
#include "../player.h"

using namespace std;

int main()
{
    Card cardOfDealer = {THREE, CLUBS};
    Player *countingPlayer = get_Counting();
    assert(countingPlayer->bet(20, 5) == 5);
    countingPlayer->expose({TWO, HEARTS});
    countingPlayer->expose({THREE, HEARTS});
    assert(countingPlayer->bet(9, 5) == 5);
    assert(countingPlayer->bet(10, 5) == 10);
    countingPlayer->shuffled();
    assert(countingPlayer->bet(10, 5) == 5);
    countingPlayer->expose({TWO, HEARTS});
    countingPlayer->expose({THREE, HEARTS});
    countingPlayer->expose({KING, HEARTS});
    assert(countingPlayer->bet(10, 5) == 5);
    countingPlayer->expose({SIX, HEARTS});
    assert(countingPlayer->bet(10, 5) == 10);

    return 0;
}