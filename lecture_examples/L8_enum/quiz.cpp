#include <iostream>
using namespace std;

enum Suit_t
{
    CLUBS,
    DIAMONDS,
    HEARTS,
    SPADES
};

int main()
{
    if (HEARTS == 2 * DIAMONDS)
    {
        cout << "ok" << endl;
    }

    cout << HEARTS - SPADES + CLUBS * DIAMONDS << endl;

    //Suit_t c = 2*HEARTS;  invalid conversion from int to Suit_t

    int array[2];
    cout << array[2 * CLUBS] << endl;
    cout << array[0] << endl; //a random value

    return 0;
}
