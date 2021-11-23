#!/bin/bash

g++ -o test_all test_all.cpp ../card.cpp ../hand.cpp
./test_all
rm -f test_all
