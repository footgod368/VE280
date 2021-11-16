#!/bin/bash

g++ -o test_simple test_simple.cpp ../player.cpp ../hand.cpp ../card.cpp
./test_simple
rm -f test_simple

g++ -o test_hard test_hard.cpp ../player.cpp ../hand.cpp ../card.cpp
./test_hard
rm -f test_hard