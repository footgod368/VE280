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
    initCreatures(creaturesNum, creaturesInfo, world);

    world.grid.width = gridWidth;
    world.grid.height = gridHeight;
    updateGrid(world);

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
    newInstruction.op = encodeOpName(nameOfOpcode);
    newInstruction.address = 0;
    if (isWithAddress(newInstruction.op))
    {
        unsigned int address;
        iss >> address;
        newInstruction.address = address;
    }
    return newInstruction;
}

opcode_t encodeOpName(string nameOfOpcode)
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

void initCreatures(const int &creaturesNum, string creaturesInfo[], world_t &world)
{
    world.numCreatures = creaturesNum;

    for (int i = 0; i < creaturesNum; i++)
    {
        creature_t newCreature;

        newCreature.programID = 0;
        string specieName;
        string dirName;
        string line = creaturesInfo[i];
        istringstream iss;
        iss.str(line);
        iss >> specieName >> dirName >> newCreature.location.r >> newCreature.location.c;
        newCreature.direction = encodeDirName(dirName);
        setSpecie(specieName, newCreature, world);

        world.creatures[i] = newCreature;
    }
}

direction_t encodeDirName(string dirName)
{
    for (int i = 0; i < 4; i++)
    {
        if (directName[i] == dirName)
            return (direction_t)i;
    }
    throw dirName;
    return (direction_t)0;
}

void setSpecie(const string &specieName, creature_t &newCreature, world_t &world)
{
    for (int i = 0; i < world.numSpecies; i++)
    {
        if (specieName == world.species[i].name)
            newCreature.species = &world.species[i];
    }
}

void updateGrid(world_t &world)
{
    for (int i = 0; i < world.grid.width; i++)
    {
        for (int j = 0; j < world.grid.height; j++)
        {
            world.grid.squares[i][j] = getCreatureInSquare(i, j, world);
        }
    }
}

creature_t *getCreatureInSquare(int i, int j, world_t &world)
{
    for (int k = 0; k < world.numCreatures; k++)
    {
        if (world.creatures[k].location.r == i && world.creatures[k].location.c == j)
            return &world.creatures[k];
    }
    return NULL;
}

void viewGrid(const world_t &world)
{
    for (int i = 0; i < world.grid.width; i++)
    {
        for (int j = 0; j < world.grid.height; j++)
        {
            if (world.grid.squares[i][j] == NULL)
                cout << "____ ";
            else
            {
                creature_t creature = *world.grid.squares[i][j];
                string name = creature.species->name.substr(0, 2);
                string direction = directShortName[creature.direction];
                cout << (name + "_" + direction + " ");
            }
        }
        cout << endl;
    }
}