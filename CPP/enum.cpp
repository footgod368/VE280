//enum
#include <iostream>
using namespace std;

enum Suit_t
{
    CLUBS,    //0
    DIAMONDS, //1
    HEARTS,   //2
    SPADES    //3
};

class Poker_card
{
private:
    Suit_t suit;
    const string suitName[4] = {"clubs", "diamonds", "hearts", "spades"}; //a smart way of display enum type
public:
    Poker_card(Suit_t suit_) { suit = (Suit_t)(suit_ + 1); }
    void viewSuit(void) { cout << suitName[suit - 1] << endl; } //legal, 'suit-1' is int, and int is needed
    bool isRed()
    {
        switch (suit)
        {
        case CLUBS:
        case HEARTS:
            return true;
        default:
            return false;
        }
    }
};

int main()
{
    Poker_card k(HEARTS);
    k.viewSuit();
    cout << k.isRed();
    return 0;
}