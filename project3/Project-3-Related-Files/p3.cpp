#include <iostream>
#include <cstdlib>
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    string speciesSummary(argv[1]);
    string worldFile(argv[2]);
    string verboseSpecifier(argv[4]);
    int totalRounds = atoi(argv[3]);
    OutputMode outputMode = Concise;
    if (verboseSpecifier == "v" || verboseSpecifier == "verbose")
        outputMode = Verbose;
    return 0;
}