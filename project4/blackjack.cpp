#include <iostream>
#include <cstdlib>
#include "player.h"
#include "deck.h"
#include "rand.h"
using namespace std;

int main(int argc, char *argv[])
{
    unsigned int bankroll = atoi(argv[1]);
    cout << bankroll << endl;
    int handsNum = atoi(argv[2]);
    cout << handsNum << endl;
    string mode(argv[3]);
    Player *player;
    if (mode == "counting")
        player = get_Counting();
    else
        player = get_Simple();

    //int cut = get_cut();

    return 0;
}