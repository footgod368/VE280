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

void oneTakeAction(int i, world_t &world, OutputMode outputMode);
void doHop(const int &i, world_t &world, OutputMode outputMode);
void doLeft(const int &i, world_t &world, OutputMode outputMode);
void doRight(const int &i, world_t &world, OutputMode outputMode);
void doInfect(const int &i, world_t &world, OutputMode outputMode);
void doIfEmpty(const int &i, world_t &world, OutputMode outputMode);
void doIfEnemy(const int &i, world_t &world, OutputMode outputMode);
void doIfSame(const int &i, world_t &world, OutputMode outputMode);
void doIfWall(const int &i, world_t &world, OutputMode outputMode);
void doGo(const int &i, world_t &world, OutputMode outputMode);

point_t sqaureFaced(const point_t &loactionNow, const direction_t &facingDir);

bool isSquareInBoundary(const point_t &square, const grid_t &grid);
bool isSquareEmpty(const point_t &square, const grid_t &grid);
bool isFacingEnemy(const creature_t &activeCreature, const grid_t &grid);

#endif