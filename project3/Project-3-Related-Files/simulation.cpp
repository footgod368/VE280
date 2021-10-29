#include <iostream>
#include "world_type.h"
#include "simulation.h"
#include <cstdlib>
#include <fstream>
#include <sstream>

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
    int gridWidth, gridHeight;
    string creaturesInfo[MAXCREATURES];
    readWorldFile(worldFile, gridWidth, gridHeight, creaturesInfo, creaturesNum);

    initSpecies(speciesNum, speciesInfo, pathOfSpecies, world);

    return world;
}

void initSpecies(const int &speciesNum, string speciesInfo[], const string &pathOfSpecies, world_t &world)
{
    world.numSpecies = speciesNum;

    for (int i = 0; i < speciesNum; i++)
    {
        species_t newSpeice;
        newSpeice.name = speciesInfo[i];

        newSpeice.programSize = 0;

        string pathOfInfo = pathOfSpecies + "/" + newSpeice.name; // ?
        ifstream fin;
        fin.open(pathOfInfo);
        string line;
        while (getline(fin, line))
        {
            if (line.empty())
                break;
            instruction_t newOpcode = getInstruction(line);
            newSpeice.program[newSpeice.programSize++] = newOpcode;
        }
        fin.close();
        world.species[i] = newSpeice;
    }
}

instruction_t getInstruction(string &line)
{
    instruction_t newInstruction;
    istringstream iss;
    iss.str(line);
    string nameOfOpcode;
    iss >> nameOfOpcode;
    newInstruction.op = encode(nameOfOpcode);
    newInstruction.address = 0;
    if (isWithAddress(newInstruction.op))
    {
        unsigned int address;
        iss >> address;
        newInstruction.address = address;
    }
    return newInstruction;
}

opcode_t encode(string nameOfOpcode)
{
    for (int i = 0; i <= 8; i++)
    {
        if (opName[i] == nameOfOpcode)
            return (opcode_t)i;
    }
    throw nameOfOpcode;
    return (opcode_t)0;
}

bool isWithAddress(opcode_t opcode)
{
    return (opcode > 3);
}