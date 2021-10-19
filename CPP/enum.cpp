//enum
#include <iostream>
using namespace std;

enum Suit_t
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

class Poker_card
{
private:
    Suit_t suit;
    const string suitName[4] = {"clubs","diamonds","hearts","spades"};
public:
    Poker_card(Suit_t suit_) { suit=suit_; }
    void viewSuit(void) { cout << suitName[suit];}
};



int main()
{
    Poker_card k(HEARTS);
    k.viewSuit;
    return 0;
}