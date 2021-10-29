#include <iostream>
#include "world_type.h"
#include "simulation.h"
#include <cstdlib>
#include <fstream>

using namespace std;

void readSpeciesSummary(const string &speciesSummary, string &pathOfSpecies, string speciesInfo[], int &speciesNum)
{
    ifstream fin;
    fin.open(speciesSummary);
    string line;
    getline(fin, line);
    pathOfSpecies = line;
    while (getline(fin, line))
    {
        speciesInfo[speciesNum++] = line;
    }
    fin.close();
}

void readWorldFile(const string &worldFile, int &gridWidth, int &gridHeight, string creaturesInfo[], int &creaturesNum)
{
    ifstream fin;
    fin.open(worldFile);
    string line;
    getline(fin, line);
    gridWidth = stoi(line);
    getline(fin, line);
    gridHeight = stoi(line);
    while (getline(fin, line))
    {
        creaturesInfo[creaturesNum++] = line;
    }
    fin.close();
}

world_t initWorld(const string &speciesSummary, const string &worldFile)
{
    world_t world;

    int speciesNum = 0;
    string pathOfSpecies;
    string speciesInfo[MAXSPECIES];
    readSpeciesSummary(speciesSummary, pathOfSpecies, speciesInfo, speciesNum);

    int creaturesNum = 0;
    int gridWidth = 0, gridHeight = 0;
    string creaturesInfo[MAXCREATURES];
    readWorldFile(worldFile, gridWidth, gridHeight, creaturesInfo, creaturesNum);

    world.numSpecies = speciesNum;
    world.numCreatures = creaturesNum;
    return world;
}