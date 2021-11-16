#!/bin/bash

rm -f result.txt

g++ -o blackjack blackjack.cpp card.cpp deck.cpp hand.cpp player.cpp rand.cpp
./blackjack 100 3 simple >test.out
diff test.out sample.txt >result.txt
rm -f blackjack test.out

cp blackjack.cpp deck.cpp hand.cpp player.cpp test-cases/
cd test-cases
make
bash runTest.sh
make clean
rm *.o