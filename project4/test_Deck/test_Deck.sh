#!/bin/bash

g++ -o test_except_shuffle test_except_shuffle.cpp ../card.cpp ../deck.cpp
./test_except_shuffle
rm -f test_except_shuffle

g++ -o test_shuffle test_shuffle.cpp ../card.cpp ../deck.cpp
./test_shuffle
rm -f test_shuffle
