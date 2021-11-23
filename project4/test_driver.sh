#!/bin/bash

g++ -o blackjack blackjack.cpp card.cpp deck.cpp hand.cpp player.cpp rand.cpp -Wall
./blackjack 100 3 simple >test.out
diff test.out sample.txt
rm -f blackjack test.out

cp blackjack.cpp deck.cpp hand.cpp player.cpp test-cases/
cd test-cases
make
bash runTest.sh
make clean
rm -f *.o
