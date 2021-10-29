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

opcode_t encodeOpName(string nameOfOpcode);

bool isWithAddress(opcode_t opcode);

void initCreatures(const int &creaturesNum, string creaturesInfo[], world_t &world);

direction_t encodeDirName(string dirName);

void setSpecie(const string &specieName, creature_t &newCreature, world_t &world);

void updateGrid(world_t &world);

creature_t *getCreatureInSquare(int i, int j, world_t &world);

void viewGrid(const world_t &world);

#endif