//enum
#include <iostream>
using namespace std;

enum Suit_t
{
    CLUBS,       //0
    DIAMONDS,    //1
    HEARTS,     //2
    SPADES      //3
};

class Poker_card
{
private:
    Suit_t suit;
    const string suitName[4] = {"clubs","diamonds","hearts","spades"}; //a smart way of display enum type
public:
    Poker_card(Suit_t suit_) { suit=suit_; }
    void viewSuit(void) { cout << suitName[suit];}
};



int main()
{
    Poker_card k(HEARTS);
    k.viewSuit();
    return 0;
}