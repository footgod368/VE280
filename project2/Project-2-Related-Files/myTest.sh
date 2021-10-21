#!/bin/bash

g++ -c myTest.cpp -Wall
g++ -c p2.cpp -Wall
g++ -c recursive.cpp -Wall
g++ -o myTest p2.o recursive.o myTest.o

./myTest

rm -f myTest *.o
