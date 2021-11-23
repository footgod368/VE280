#include <iostream>
#include <cassert>
#include "../player.h"

using namespace std;

int main()
{
    unsigned int bankroll = 20;
    unsigned int minimum = 5;
    Card cardOfDealer = {THREE, CLUBS};
    Player *simplePlayer = get_Simple();
    assert(simplePlayer->bet(20, 5) == 5);
    Hand hardHand;
    hardHand.addCard({TWO, HEARTS});
    assert(simplePlayer->draw(cardOfDealer, hardHand));
    hardHand.addCard({THREE, HEARTS});
    assert(simplePlayer->draw(cardOfDealer, hardHand));
    hardHand.addCard({SIX, HEARTS});
    assert(simplePlayer->draw(cardOfDealer, hardHand));
    hardHand.addCard({ACE, HEARTS});
    assert(simplePlayer->draw(cardOfDealer, hardHand));
    hardHand.addCard({ACE, HEARTS});
    assert(!simplePlayer->draw(cardOfDealer, hardHand));
    hardHand.addCard({FOUR, HEARTS});
    assert(!simplePlayer->draw(cardOfDealer, hardHand));

    Hand softHand;
    softHand.addCard({ACE, HEARTS});
    assert(simplePlayer->draw(cardOfDealer, softHand));
    softHand.addCard({SIX, HEARTS});
    assert(simplePlayer->draw(cardOfDealer, softHand));
    softHand.addCard({ACE, HEARTS});
    assert(simplePlayer->draw(cardOfDealer, softHand));
    cardOfDealer = {TWO, CLUBS};
    assert(!simplePlayer->draw(cardOfDealer, softHand));
    softHand.addCard({ACE, HEARTS});
    assert(!simplePlayer->draw(cardOfDealer, softHand));
    
    softHand.addCard({THREE, HEARTS});
    assert(simplePlayer->draw(cardOfDealer, softHand));
    cardOfDealer = {FOUR, CLUBS};
    assert(!simplePlayer->draw(cardOfDealer, softHand));
    

    return 0;
}