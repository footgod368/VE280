#!/bin/bash

g++ -c myTest.cpp
g++ -c p2.cpp
g++ -c recursive.cpp
g++ -o myTest p2.o recursive.o myTest.o

./myTest

rm -f myTest *.o
