#!/bin/bash

g++ -c chen_test.cpp
g++ -c p2.cpp
g++ -c recursive.cpp
g++ -Wall -o chen_test p2.o recursive.o chen_test.o

./chen_test

rm -f chen_test *.o
