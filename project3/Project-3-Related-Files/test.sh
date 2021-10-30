#!/bin/bash

rm -f *.o p3 main
g++ -o p3 p3.cpp simulation.cpp

for ((i=1; i<=3; i++))
do
    ./p3 species world-tests/world${i} 
done