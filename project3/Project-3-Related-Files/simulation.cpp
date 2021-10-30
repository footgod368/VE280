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
    newInstruction.address = -1;
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

void oneTakeAction(int i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    string speciesName = activeCreature.species->name;
    string direction = directName[activeCreature.direction];
    int row = activeCreature.location.r;
    int col = activeCreature.location.c;
    if (outputMode == Concise)
        cout << "Creature (" << speciesName << " " << direction << " " << row << " " << col << ") takes action: " << flush;
    else
        cout << "Creature (" << speciesName << " " << direction << " " << row << " " << col << ") takes action:" << endl;
    instruction_t instructionNow;
    do
    {
        instructionNow = activeCreature.species->program[activeCreature.programID];
        switch (instructionNow.op)
        {
        case HOP:
            doHop(i, world, outputMode);
            break;
        case LEFT:
            doLeft(i, world, outputMode);
            break;
        case RIGHT:
            doRight(i, world, outputMode);
            break;
        case INFECT:
            doInfect(i, world, outputMode);
            break;
        case IFEMPTY:
            doIfEmpty(i, world, outputMode);
            break;
        case IFENEMY:
            doIfEnemy(i, world, outputMode);
            break;
        case IFSAME:
            doIfSame(i, world, outputMode);
            break;
        case IFWALL:
            doIfWall(i, world, outputMode);
            break;
        case GO:
            doGo(i, world, outputMode);
            break;
        default:
            throw instructionNow.op;
            break;
        }
    } while (instructionNow.op > 3);
}

void doHop(const int &i, world_t &world, OutputMode outputMode)
{
}
void doLeft(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Concise)
        cout << "left" << endl;
    else
        cout << "Instruction " << (activeCreature.programID + 1) << ": left" << endl;
    switch (activeCreature.direction)
    {
    case NORTH:
        activeCreature.direction = WEST;
        break;
    case WEST:
        activeCreature.direction = SOUTH;
        break;
    case SOUTH:
        activeCreature.direction = EAST;
        break;
    case EAST:
        activeCreature.direction = NORTH;
        break;
    default:
        throw activeCreature.direction;
        break;
    }
    activeCreature.programID += 1;
    updateGrid(world);
    viewGrid(world);
}
void doRight(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Concise)
        cout << "right" << endl;
    else
        cout << "Instruction " << (activeCreature.programID + 1) << ": right" << endl;
    switch (activeCreature.direction)
    {
    case NORTH:
        activeCreature.direction = EAST;
        break;
    case WEST:
        activeCreature.direction = NORTH;
        break;
    case SOUTH:
        activeCreature.direction = WEST;
        break;
    case EAST:
        activeCreature.direction = SOUTH;
        break;
    default:
        throw activeCreature.direction;
        break;
    }
    activeCreature.programID += 1;
    updateGrid(world);
    viewGrid(world);
}
void doInfect(const int &i, world_t &world, OutputMode outputMode)
{
}
void doIfEmpty(const int &i, world_t &world, OutputMode outputMode)
{
}
void doIfEnemy(const int &i, world_t &world, OutputMode outputMode)
{
}
void doIfSame(const int &i, world_t &world, OutputMode outputMode)
{
}
void doIfWall(const int &i, world_t &world, OutputMode outputMode)
{
}
void doGo(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
}