#include <iostream>
#include <cassert>
#include "../deck.h"
using namespace std;

int main()
{
    Deck newDeck;
    newDeck.shuffle(26);

    Card cardDealt_1_shuffle1 = newDeck.deal();
    Card cardDealt_2_shuffle1 = newDeck.deal();
    for (int i = 3; i <= 51; i++)
        newDeck.deal();
    Card cardDealt_52_shuffle1 = newDeck.deal();

    newDeck.shuffle(20);
    Card cardDealt_1_shuffle2 = newDeck.deal();
    for (int i = 2; i <= 51; i++)
        newDeck.deal();
    Card cardDealt_52_shuffle2 = newDeck.deal();

    newDeck.shuffle(0);
    Card cardDealt_1_shuffle3 = newDeck.deal();

    newDeck.shuffle(52);
    Card cardDealt_1_shuffle4 = newDeck.deal();

    bool shuffle1 = cardDealt_1_shuffle1.suit == CLUBS && cardDealt_1_shuffle1.spot == TWO &&
                    cardDealt_2_shuffle1.suit == SPADES && cardDealt_2_shuffle1.spot == TWO &&
                    cardDealt_52_shuffle1.suit == HEARTS && cardDealt_52_shuffle1.spot == ACE;
    bool shuffle2 = cardDealt_1_shuffle2.suit == 2 && cardDealt_1_shuffle2.spot == 10 &&
                    cardDealt_52_shuffle2.suit == HEARTS && cardDealt_52_shuffle2.spot == ACE;
    bool shuffle3 = cardDealt_1_shuffle3.suit == 2 && cardDealt_1_shuffle3.spot == 10;
    bool shuffle4 = cardDealt_1_shuffle4.suit == 2 && cardDealt_1_shuffle4.spot == 10;

    if (shuffle1 && shuffle2 && shuffle3 && shuffle4)
        return 0;
    cerr << "test_shuffle failed" << endl;
    return 1;
}