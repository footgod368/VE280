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

world_t initWorld(const string &speciesSummary, const string &worldFile);

void initSpecies(const int &speciesNum, string speciesInfo[], const string &pathOfSpecies, world_t &world);

instruction_t getInstruction(string &line);

opcode_t encode(string nameOfOpcode);

bool isWithAddress(opcode_t opcode);

#endif