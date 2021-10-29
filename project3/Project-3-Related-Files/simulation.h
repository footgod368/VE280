#ifndef SIMULATION_H
#define SIMULATION_H

using namespace std;

enum OutputMode
{
    Verbose,
    Concise
};

void readSpeciesSummary(const string &speciesSummary, string &pathOfSpecies, string speciesInfo[], int &speciesNum);

void readWorldFile(const string &worldFile, int &gridWidth, int &gridHeight, string creaturesinfo[], int &creaturesNum);

#endif