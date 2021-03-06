#include <iostream>using namespace std;

enum Suit_t
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
}

;

bool isRed(Suit_t s)
{
    // switch (s) {
    //     case DIAMONDS:
    //     case HEARTS:
    //         return true;
    //         break;
    //     case CLUBS:
    //     case SPADES:
    //         return false;
    //         break;
    //     default:
    //         assert(0);
    //         break;
    // }
    return s == 1 || s == 2; //整数值可用来判断，但不能用来赋值
}

int main()
{
    Suit_t suit = DIAMONDS;

    if (isRed(suit))
    {
        cout << "red" << endl;
    }

    cout << suit << endl; // automatically converted to int

    //Suit_t suit2 = 2; // Need to cast to Suit_t

    return 0;
}