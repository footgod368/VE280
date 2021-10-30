#include <iostream>
#include "world_type.h"
#include "simulation.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cassert>
using namespace std;

void readSpeciesSummary(const string &speciesSummary, string &pathOfSpecies, string speciesInfo[], int &speciesNum)
{
    ifstream fin;
    try
    {
        fin.open(speciesSummary);
        if (!fin)
            throw speciesSummary;
    }
    catch (string path)
    {
        cout << "Cannot open file " << path << "!" << endl;
        throw path;
    }
    string line;
    getline(fin, line);
    pathOfSpecies = line;
    while (getline(fin, line))
    {
        try
        {
            if ((unsigned int)speciesNum >= MAXSPECIES)
                throw speciesNum;
        }
        catch (int excessSpeciesNum)
        {
            cout << "Error: Too many species!" << endl
                 << "Maximal number of species is " << MAXSPECIES << "." << endl;
            throw excessSpeciesNum;
        }
        speciesInfo[speciesNum++] = line;
    }
    fin.close();
}

void readWorldFile(const string &worldFile, int &gridWidth, int &gridHeight, string creaturesInfo[], int &creaturesNum)
{
    ifstream fin;
    try
    {
        fin.open(worldFile);
        if (!fin)
            throw worldFile;
    }
    catch (string path)
    {
        cout << "Cannot open file " << path << "!" << endl;
    }
    string line;
    getline(fin, line);
    gridHeight = stoi(line);
    try
    {
        if (gridHeight < 1 || (unsigned int)gridHeight > MAXHEIGHT)
            throw gridHeight;
    }
    catch (int illegalGridHeight)
    {
        cout << "Error: The grid height is illegal!" << endl;
        throw illegalGridHeight;
    }
    getline(fin, line);
    gridWidth = stoi(line);
    try
    {
        if (gridWidth < 1 || (unsigned int)gridWidth > MAXWIDTH)
            throw gridWidth;
    }
    catch (int illegalGridWidth)
    {
        cout << "Error: The grid width is illegal!" << endl;
        throw illegalGridWidth;
    }
    while (getline(fin, line))
    {
        try
        {
            if ((unsigned int)creaturesNum >= MAXCREATURES)
                throw creaturesNum;
        }
        catch (int creaturesNum)
        {
            cout << "Too many creatures!" << endl
                 << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
            throw creaturesNum;
        }
        creaturesInfo[creaturesNum++] = line;
    }
    fin.close();
}

void initWorld(const string &speciesSummary, const string &worldFile, world_t &world)
{

    int speciesNum = 0;
    string pathOfSpecies;
    string speciesInfo[MAXSPECIES];
    readSpeciesSummary(speciesSummary, pathOfSpecies, speciesInfo, speciesNum);

    int creaturesNum = 0;
    int gridWidth, gridHeight;
    string creaturesInfo[MAXCREATURES];
    readWorldFile(worldFile, gridWidth, gridHeight, creaturesInfo, creaturesNum);
    world.grid.width = gridWidth;
    world.grid.height = gridHeight;
    initSpecies(speciesNum, speciesInfo, pathOfSpecies, world);

    initCreatures(creaturesNum, creaturesInfo, world);

    updateGrid(world);
}

void initSpecies(const int &speciesNum, string speciesInfo[], const string &pathOfSpecies, world_t &world)
{
    world.numSpecies = speciesNum;

    for (int i = 0; i < speciesNum; i++)
    {
        species_t newSpeice;
        newSpeice.name = speciesInfo[i];

        newSpeice.programSize = 0;

        string pathOfInfo = pathOfSpecies + "/" + newSpeice.name;
        ifstream fin;
        try
        {
            fin.open(pathOfInfo);
            if (!fin)
                throw pathOfInfo;
        }
        catch (string path)
        {
            cout << "Cannot open file " << path << "!" << endl;
            throw path;
        }
        string line;
        while (getline(fin, line))
        {
            if (line.empty())
                break;
            instruction_t newOpcode = getInstruction(line);
            try
            {
                if (newSpeice.programSize > MAXPROGRAM)
                    throw newSpeice.name;
            }
            catch (string specieName)
            {
                cout << "Too many instructions for species " << specieName << "!" << endl
                     << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
                throw specieName;
            }
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
    try
    {
        newInstruction.op = encodeOpName(nameOfOpcode);
    }
    catch (string illegalInstruction)
    {
        cout << "Error: Instruction " << illegalInstruction << " is not recognized!" << endl;
        throw illegalInstruction;
    }
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
        try
        {
            if (!isSquareInBoundary(newCreature.location, world.grid))
                throw newCreature;
        }
        catch (creature_t newCreature)
        {
            cout << "Error: Creature (" << line << ") is out of bound!" << endl
                 << "The grid size is " << world.grid.height << "-by-" << world.grid.width << endl;
            throw newCreature.location;
        }

        try
        {
            newCreature.direction = encodeDirName(dirName);
        }
        catch (string unknownDirName)
        {
            cout << "Error: Direction " << unknownDirName << " is not recognized!" << endl;
            throw unknownDirName;
        }
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
    bool isInSpeciesList = false;
    for (unsigned int i = 0; i < world.numSpecies; i++)
    {
        if (specieName == world.species[i].name)
        {
            newCreature.species = &world.species[i];
            isInSpeciesList = true;
        }
    }
    try
    {
        if (!isInSpeciesList)
            throw specieName;
    }
    catch (string UnknownSpeciesName)
    {
        cout << "Species " << UnknownSpeciesName << " not found!" << endl;
        throw UnknownSpeciesName;
    }
}

void updateGrid(world_t &world)
{
    for (unsigned int i = 0; i < world.grid.height; i++)
    {
        for (unsigned int j = 0; j < world.grid.width; j++)
        {
            world.grid.squares[i][j] = getCreatureInSquare(i, j, world);
        }
    }
}

creature_t *getCreatureInSquare(int i, int j, world_t &world)
{
    for (unsigned int k = 0; k < world.numCreatures; k++)
    {
        if (world.creatures[k].location.r == i && world.creatures[k].location.c == j)
            return &world.creatures[k];
    }
    return NULL;
}

void viewGrid(const world_t &world)
{
    for (unsigned int i = 0; i < world.grid.height; i++)
    {
        for (unsigned int j = 0; j < world.grid.width; j++)
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
            assert(0);
            break;
        }
    } while (instructionNow.op > 3);
}

void doHop(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    if (outputMode == Concise)
        cout << "hop" << endl;
    else
        cout << "Instruction " << (activeCreature.programID + 1) << ": hop" << endl;
    if (isLegalHop(activeCreature, world.grid))
    {
        activeCreature.location = sqaureFaced(activeCreature.location, activeCreature.direction);
    }
    activeCreature.programID += 1;
    updateGrid(world);
    if (outputMode == Verbose)
        viewGrid(world);
}
void doLeft(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
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
        assert(0);
        break;
    }
    activeCreature.programID += 1;
    updateGrid(world);
    if (outputMode == Verbose)
        viewGrid(world);
}
void doRight(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
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
        assert(0);
        break;
    }
    activeCreature.programID += 1;
    updateGrid(world);
    if (outputMode == Verbose)
        viewGrid(world);
}
void doInfect(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    if (outputMode == Concise)
        cout << "infect" << endl;
    else
        cout << "Instruction " << (activeCreature.programID + 1) << ": infect" << endl;
    point_t facedSquare = sqaureFaced(activeCreature.location, activeCreature.direction);
    if (isFacingEnemy(activeCreature, world.grid))
    {
        creature_t *ptFacedCreature = getCreatureInSquare(facedSquare.r, facedSquare.c, world);
        ptFacedCreature->species = activeCreature.species;
        ptFacedCreature->programID = 0;
    }
    activeCreature.programID += 1;
    updateGrid(world);
    if (outputMode == Verbose)
        viewGrid(world);
}
void doIfEmpty(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Verbose)
        cout << "Instruction " << (activeCreature.programID + 1) << ": ifempty " << instructionNow.address << endl;
    point_t facedSquare = sqaureFaced(activeCreature.location, activeCreature.direction);
    bool isInBoundary = isSquareInBoundary(facedSquare, world.grid);
    bool isEmpty = isSquareEmpty(facedSquare, world.grid);
    if (isInBoundary && isEmpty)
        activeCreature.programID = instructionNow.address - 1;
    else
        activeCreature.programID += 1;
}
void doIfEnemy(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Verbose)
        cout << "Instruction " << (activeCreature.programID + 1) << ": ifenemy " << instructionNow.address << endl;
    if (isFacingEnemy(activeCreature, world.grid))
        activeCreature.programID = instructionNow.address - 1;
    else
        activeCreature.programID += 1;
}
void doIfSame(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Verbose)
        cout << "Instruction " << (activeCreature.programID + 1) << ": ifsame " << instructionNow.address << endl;
    if (isFacingSame(activeCreature, world.grid))
        activeCreature.programID = instructionNow.address - 1;
    else
        activeCreature.programID += 1;
}
void doIfWall(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Verbose)
        cout << "Instruction " << (activeCreature.programID + 1) << ": ifwall " << instructionNow.address << endl;
    point_t facedSquare = sqaureFaced(activeCreature.location, activeCreature.direction);
    if (!isSquareInBoundary(facedSquare, world.grid))
        activeCreature.programID = instructionNow.address - 1;
    else
        activeCreature.programID += 1;
}
void doGo(const int &i, world_t &world, OutputMode outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Verbose)
        cout << "Instruction " << (activeCreature.programID + 1) << ": go " << instructionNow.address << endl;
    activeCreature.programID = instructionNow.address - 1;
}

point_t sqaureFaced(const point_t &loactionNow, const direction_t &facingDir)
{
    point_t facedSquare = loactionNow;
    switch (facingDir)
    {
    case EAST:
        facedSquare.c += 1;
        return facedSquare;
        break;
    case WEST:
        facedSquare.c -= 1;
        return facedSquare;
        break;
    case NORTH:
        facedSquare.r -= 1;
        return facedSquare;
        break;
    case SOUTH:
        facedSquare.r += 1;
        return facedSquare;
        break;
    default:
        assert(0);
        return facedSquare;
        break;
    }
}

bool isSquareInBoundary(const point_t &square, const grid_t &grid)
{
    return square.r >= 0 && (unsigned int)square.r < grid.height && square.c >= 0 && (unsigned int)square.c < grid.width;
}

bool isSquareEmpty(const point_t &square, const grid_t &grid)
{
    int row = square.r;
    int col = square.c;
    return grid.squares[row][col] == NULL;
}

bool isFacingEnemy(const creature_t &activeCreature, const grid_t &grid)
{
    point_t facedSquare = sqaureFaced(activeCreature.location, activeCreature.direction);
    if (isSquareInBoundary(facedSquare, grid))
    {
        if (!isSquareEmpty(facedSquare, grid))
        {
            return activeCreature.species->name != grid.squares[facedSquare.r][facedSquare.c]->species->name;
        }
        else
            return false;
    }
    else
        return false;
}

bool isFacingSame(const creature_t &activeCreature, const grid_t &grid)
{
    point_t facedSquare = sqaureFaced(activeCreature.location, activeCreature.direction);
    if (isSquareInBoundary(facedSquare, grid))
    {
        if (!isSquareEmpty(facedSquare, grid))
        {
            return activeCreature.species->name == grid.squares[facedSquare.r][facedSquare.c]->species->name;
        }
        else
            return false;
    }
    else
        return false;
}

bool isLegalHop(const creature_t &activeCreature, const grid_t &grid)
{
    point_t facedSquare = sqaureFaced(activeCreature.location, activeCreature.direction);
    if (isSquareInBoundary(facedSquare, grid))
        return isSquareEmpty(facedSquare, grid);
    else
        return false;
}

void checkArgc(int argc)
{
    if (argc < 4)
    {
        cout << "Error: Missing arguments!" << endl
             << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
        throw argc;
    }
}

void checkRoundsNum(int roundsNum)
{
    if (roundsNum < 0)
    {
        cout << "Error: Number of simulation rounds is negative!" << endl;
        throw roundsNum;
    }
}
