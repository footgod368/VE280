#include <iostream>
#include <string>
#include <chrono>
#include "lab6.h"

using namespace std;

/**
 * The main function, we don not need to change this.
 * All inputs and outputs are taken care of here.
 * @return
 */
int main(int argc, char *argv[])
{
    if (argc == 2 && string(argv[1]) == "-r")
    {
        // Race mode, used by server to compete with each other
        Game &game = *getMyGame();
        Brain &brain = *getMyBrain();

        int myX, myY, oppX, oppY;
        cin >> myX >> myY;
        cin >> oppX >> oppY;

        int myD, oppD;
        cin >> myD >> oppD;

        game.initialize(myX, myY, oppX, oppY, Direction(myD), Direction(oppD));
        brain.initialize();

        do
        {
            Move m = brain.judge();
            cout << int(m) << endl;

            int oppMove;
            cin >> oppMove;

            game.move(Tank_A, m);
            game.move(Tank_B, Move(oppMove));
        } while (game.TurnStatus() == T_Cont);
    }
    else
    {
        Game &game = *getMyGame();

        int myX, myY, oppX, oppY;
        cin >> myX >> myY;
        cin >> oppX >> oppY;

        int myD, oppD;
        cin >> myD >> oppD;
        game.initialize(myX, myY, oppX, oppY, Direction(myD), Direction(oppD));

        TurnStatus turn_status;

        do
        {
            cout << game.draw() << endl;
            auto start = chrono::steady_clock::now();
            while (chrono::duration<double>(chrono::steady_clock::now() - start).count() < 0.2)
                ;

            int myMove;
            cin >> myMove;

            int oppMove;
            cin >> oppMove;

            game.move(Tank_A, Move(myMove));
            game.move(Tank_B, Move(oppMove));
        } while ((turn_status = game.TurnStatus()) == T_Cont);

        switch (turn_status)
        {
        case T_A_Win:
            cout << "Tank A Wins" << endl;
            break;
        case T_B_Win:
            cout << "Tank B Wins" << endl;
            break;
        case T_Draw:
            cout << "Draw" << endl;
            break;
        default:
            cout << "Something Wrong Happened" << endl;
            break;
        }
    }
    return 0;
}
