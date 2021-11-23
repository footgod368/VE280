#include <iostream>
#include <cassert>
#include "../deck.h"
using namespace std;

int main()
{
    Deck newDeck;
    assert(newDeck.cardsLeft() == 52);
    Card cardDealt_1 = newDeck.deal();
    Card cardDealt_2 = newDeck.deal();
    assert(newDeck.cardsLeft() == 50);

    for (int i = 3; i <= 30; i++)
        newDeck.deal();
    assert(newDeck.cardsLeft() == 22);

    Card cardDealt_31 = newDeck.deal();
    for (int i = 32; i <= 51; i++)
        newDeck.deal();
    assert(newDeck.cardsLeft() == 1);

    Card cardDealt_52 = newDeck.deal();
    assert(newDeck.cardsLeft() == 0);

    try
    {
        newDeck.deal();
    }
    catch (DeckEmpty deckEmpty)
    {
        newDeck.reset();
        Card cardDealtAfterReset = newDeck.deal();

        if (cardDealt_1.suit == SPADES && cardDealt_1.spot == TWO &&
            cardDealt_2.suit == SPADES && cardDealt_2.spot == THREE &&
            cardDealt_31.suit == CLUBS && cardDealt_31.spot == SIX &&
            cardDealt_52.suit == DIAMONDS && cardDealt_52.spot == ACE &&
            cardDealtAfterReset.suit == SPADES && cardDealtAfterReset.spot == TWO)
            return 0;
    }

    cerr << "test_except_shuffle failed" << endl;
    return 1;
}