#include <iostream>
#include <cstdlib>
#include <string>
#include "world_type.h"
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    string speciesSummary(argv[1]);
    string worldFile(argv[2]);
    string verboseSpecifier(argv[4]);
    int roundsNum = atoi(argv[3]);
    OutputMode outputMode = Concise;
    if (verboseSpecifier == "v" || verboseSpecifier == "verbose")
        outputMode = Verbose;

    int speciesNum = 0;
    string pathOfSpecies;
    string speciesInfo[MAXSPECIES];
    readSpeciesSummary(speciesSummary, pathOfSpecies, speciesInfo, speciesNum);

    int creaturesNum = 0;
    int gridWidth = 0, gridHeight = 0;
    string creaturesInfo[MAXCREATURES];
    readWorldFile(worldFile, gridWidth, gridHeight, creaturesInfo, creaturesNum);

    return 0;
}