#!/bin/bash

g++ -o blackjack blackjack.cpp card.cpp deck.cpp hand.cpp player.cpp rand.cpp
./blackjack $1 $2 $3 > test.out
diff test.out sample.txt > result.txt
rm -f blackjack test.out