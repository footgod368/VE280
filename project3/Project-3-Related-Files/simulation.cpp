#include <iostream>
#include "world_type.h"
#include "simulation.h"
#include <cstdlib>
#include <fstream>
#include <sstream>
#include <cassert>
#include <string>
using namespace std;

void handleMissingArguments(const Error &error)
{
    cout << "Error: Missing arguments!" << endl
         << "Usage: ./p3 <species-summary> <world-file> <rounds> [v|verbose]" << endl;
}
void handleNegativeRoundsNum(const Error &error)
{
    cout << "Error: Number of simulation rounds is negative!" << endl;
}
void handleIfileFail(const Error &error)
{
    string wrongPath = error.info;
    cout << "Error: Cannot open file " << wrongPath << "!" << endl;
}
void handleExcessSpeciesNum(const Error &error)
{
    cout << "Error: Too many species!" << endl
         << "Maximal number of species is " << MAXSPECIES << "." << endl;
}
void handleExcessInstructionsNum(const Error &error)
{
    string specieName = error.info;
    cout << "Error: Too many instructions for species " << specieName << "!" << endl
         << "Maximal number of instructions is " << MAXPROGRAM << "." << endl;
}
void handleUnknownInstruction(const Error &error)
{
    string illegalInstruction = error.info;
    cout << "Error: Instruction " << illegalInstruction << " is not recognized!" << endl;
}
void handleExcessCreaturesNum(const Error &error)
{
    cout << "Error: Too many creatures!" << endl
         << "Maximal number of creatures is " << MAXCREATURES << "." << endl;
}
void handleUnknownSpecies(const Error &error)
{
    string unknownSpeciesName(error.info);
    cout << "Error: Species " << unknownSpeciesName << " not found!" << endl;
}
void handleUnknownDirection(const Error &error)
{
    string unknownDirName(error.info);
    cout << "Error: Direction " << unknownDirName << " is not recognized!" << endl;
}
void handleIllegalGridWidth(const Error &error)
{
    cout << "Error: The grid width is illegal!" << endl;
}
void handleIllegalGridHeight(const Error &error)
{
    cout << "Error: The grid height is illegal!" << endl;
}
void handleCreatureOutOfBound(const Error &error)
{
    int gridHeight = 0, gridWidth = 0;
    string creatureInfo;
    istringstream iss(error.info);
    iss >> gridHeight >> gridWidth;
    iss.get();
    getline(iss, creatureInfo);
    cout << "Error: Creature (" << creatureInfo << ") is out of bound!" << endl
         << "The grid size is " << gridHeight << "-by-" << gridWidth << "." << endl;
}
void handleCreatureOverlap(const Error &error)
{
    cout << error.info << endl;
}
void handleError(const Error &error)
{
    switch (error.type)
    {
    case MissingArguments:
        handleMissingArguments(error);
        break;
    case NegativeRoundsNum:
        handleNegativeRoundsNum(error);
        break;
    case IfileFail:
        handleIfileFail(error);
        break;
    case ExcessSpeciesNum:
        handleExcessSpeciesNum(error);
        break;
    case ExcessInstructionsNum:
        handleExcessInstructionsNum(error);
        break;
    case UnknownInstruction:
        handleUnknownInstruction(error);
        break;
    case ExcessCreaturesNum:
        handleExcessCreaturesNum(error);
        break;
    case UnknownSpecies:
        handleUnknownSpecies(error);
        break;
    case UnknownDirection:
        handleUnknownDirection(error);
        break;
    case IllegalGridWidth:
        handleIllegalGridWidth(error);
        break;
    case IllegalGridHeight:
        handleIllegalGridHeight(error);
        break;
    case CreatureOutOfBound:
        handleCreatureOutOfBound(error);
        break;
    case CreatureOverlap:
        handleCreatureOverlap(error);
        break;
    default:
        break;
    }
}

void readSpeciesSummary(const string &speciesSummary, string &pathOfSpecies, string speciesInfo[], int &speciesNum)
{
    ifstream fin;
    fin.open(speciesSummary);
    if (!fin)
    {
        Error error(IfileFail, speciesSummary);
        throw error;
    }
    string line;
    getline(fin, line);
    pathOfSpecies = line;
    while (getline(fin, line))
    {

        if ((unsigned int)speciesNum >= MAXSPECIES)
        {
            Error error(ExcessSpeciesNum);
            throw error;
        }

        speciesInfo[speciesNum++] = line;
    }
    fin.close();
}

void readWorldFile(const string &worldFile, int &gridWidth, int &gridHeight, string creaturesInfo[], int &creaturesNum)
{
    ifstream fin;
    fin.open(worldFile);
    if (!fin)
    {
        Error error(IfileFail, worldFile);
        throw error;
    }
    string line;
    getline(fin, line);
    gridHeight = stoi(line);
    if (gridHeight < 1 || (unsigned int)gridHeight > MAXHEIGHT)
    {
        Error error(IllegalGridHeight);
        throw error;
    }
    getline(fin, line);
    gridWidth = stoi(line);

    if (gridWidth < 1 || (unsigned int)gridWidth > MAXWIDTH)
    {
        Error error(IllegalGridWidth);
        throw error;
    }
    while (getline(fin, line))
    {

        if ((unsigned int)creaturesNum >= MAXCREATURES)
        {
            Error error(ExcessCreaturesNum);
            throw error;
        }

        creaturesInfo[creaturesNum++] = line;
    }
    fin.close();
}

void initWorld(const DataForInit &dataForInit, world_t &world)
{
    string speciesSummary = dataForInit.speciesSummary;
    string worldFile = dataForInit.worldFile;

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

    checkOverlapped(world);

    updateGrid(world);
}

void initSpecies(const int &speciesNum, string speciesInfo[], const string &pathOfSpecies, world_t &world)
{
    world.numSpecies = speciesNum;

    for (int i = 0; i < speciesNum; i++)
    {
        species_t &newSpeice = world.species[i];
        newSpeice.name = speciesInfo[i];

        newSpeice.programSize = 0;

        string pathOfInfo = pathOfSpecies + "/" + newSpeice.name;
        ifstream fin;

        fin.open(pathOfInfo);
        if (!fin)
        {
            Error error(IfileFail, pathOfInfo);
            throw error;
        }
        string line;
        while (getline(fin, line))
        {
            if (line.empty())
                break;
            instruction_t newOpcode = getInstruction(line);

            if (newSpeice.programSize >= MAXPROGRAM)
            {
                Error error(ExcessInstructionsNum, newSpeice.name);
                throw error;
            }
            newSpeice.program[newSpeice.programSize++] = newOpcode;
        }
        fin.close();
    }
}

instruction_t getInstruction(const string &line)
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

opcode_t encodeOpName(const string &nameOfOpcode)
{
    for (int i = 0; i <= 8; i++)
    {
        if (opName[i] == nameOfOpcode)
            return (opcode_t)i;
    }
    Error error(UnknownInstruction, nameOfOpcode);
    throw error;
    return (opcode_t)0;
}

bool isWithAddress(const opcode_t &opcode)
{
    return (opcode > 3);
}

void initCreatures(const int &creaturesNum, const string creaturesInfo[], world_t &world)
{
    world.numCreatures = creaturesNum;

    for (int i = 0; i < creaturesNum; i++)
    {
        creature_t &newCreature = world.creatures[i];

        newCreature.programID = 0;
        string specieName;
        string dirName;
        string line = creaturesInfo[i];
        istringstream iss;
        iss.str(line);
        iss >> specieName >> dirName >> newCreature.location.r >> newCreature.location.c;

        if (!isSquareInBoundary(newCreature.location, world.grid))
        {
            string errorInfo(to_string(world.grid.height) + " " + to_string(world.grid.width) + " " + line);
            Error error(CreatureOutOfBound, errorInfo);
            throw error;
        }

        newCreature.direction = encodeDirName(dirName);

        setSpecie(specieName, newCreature, world);
    }
}

direction_t encodeDirName(const string &dirName)
{
    for (int i = 0; i < 4; i++)
    {
        if (directName[i] == dirName)
            return (direction_t)i;
    }
    Error error(UnknownDirection, dirName);
    throw error;
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

    if (!isInSpeciesList)
    {
        Error error(UnknownSpecies, specieName);
        throw error;
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

creature_t *getCreatureInSquare(const int &i, const int &j, world_t &world)
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

void oneCreatureAct(const int &i, world_t &world, const OutputMode &outputMode)
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
    } while (isWithAddress(instructionNow.op));
}

void doHop(const int &i, world_t &world, const OutputMode &outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    if (outputMode == Concise)
        cout << "hop" << endl;
    else
        cout << "Instruction " << (activeCreature.programID + 1) << ": hop" << endl;
    if (isLegalHop(activeCreature, world.grid))
    {
        activeCreature.location = sqaureFaced(activeCreature);
    }
    activeCreature.programID += 1;
    updateGrid(world);
    if (outputMode == Verbose)
        viewGrid(world);
}
void doLeft(const int &i, world_t &world, const OutputMode &outputMode)
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
void doRight(const int &i, world_t &world, const OutputMode &outputMode)
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
void doInfect(const int &i, world_t &world, const OutputMode &outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    if (outputMode == Concise)
        cout << "infect" << endl;
    else
        cout << "Instruction " << (activeCreature.programID + 1) << ": infect" << endl;
    point_t facedSquare = sqaureFaced(activeCreature);
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
void doIfEmpty(const int &i, world_t &world, const OutputMode &outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Verbose)
        cout << "Instruction " << (activeCreature.programID + 1) << ": ifempty " << instructionNow.address << endl;
    point_t facedSquare = sqaureFaced(activeCreature);
    bool isInBoundary = isSquareInBoundary(facedSquare, world.grid);
    bool isEmpty = isSquareEmpty(facedSquare, world.grid);
    if (isInBoundary && isEmpty)
        activeCreature.programID = instructionNow.address - 1;
    else
        activeCreature.programID += 1;
}
void doIfEnemy(const int &i, world_t &world, const OutputMode &outputMode)
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
void doIfSame(const int &i, world_t &world, const OutputMode &outputMode)
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
void doIfWall(const int &i, world_t &world, const OutputMode &outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Verbose)
        cout << "Instruction " << (activeCreature.programID + 1) << ": ifwall " << instructionNow.address << endl;
    point_t facedSquare = sqaureFaced(activeCreature);
    if (!isSquareInBoundary(facedSquare, world.grid))
        activeCreature.programID = instructionNow.address - 1;
    else
        activeCreature.programID += 1;
}
void doGo(const int &i, world_t &world, const OutputMode &outputMode)
{
    creature_t &activeCreature = world.creatures[i];
    instruction_t instructionNow = activeCreature.species->program[activeCreature.programID];
    if (outputMode == Verbose)
        cout << "Instruction " << (activeCreature.programID + 1) << ": go " << instructionNow.address << endl;
    activeCreature.programID = instructionNow.address - 1;
}

point_t sqaureFaced(const creature_t &activeCreature)
{
    point_t locationNow = activeCreature.location;
    direction_t facingDir = activeCreature.direction;

    point_t facedSquare = locationNow;
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
    point_t facedSquare = sqaureFaced(activeCreature);
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
    point_t facedSquare = sqaureFaced(activeCreature);
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
    point_t facedSquare = sqaureFaced(activeCreature);
    if (isSquareInBoundary(facedSquare, grid))
        return isSquareEmpty(facedSquare, grid);
    else
        return false;
}

void checkArgc(const int &argc)
{
    if (argc < 4)
    {
        Error error(MissingArguments);
        throw error;
    }
}

void checkRoundsNum(const int &roundsNum)
{
    if (roundsNum < 0)
    {
        Error error(NegativeRoundsNum);
        throw error;
    }
}

string renderOverlappedInfo(const creature_t &firstCreature, const creature_t &secondCreature)
{
    string firstInfo(firstCreature.species->name + " " + directName[firstCreature.direction] + " " + to_string(firstCreature.location.r) + " " + to_string(firstCreature.location.c));
    string secondInfo(secondCreature.species->name + " " + directName[secondCreature.direction] + " " + to_string(secondCreature.location.r) + " " + to_string(secondCreature.location.c));
    return "Error: Creature (" + secondInfo + ") overlaps with creature (" + firstInfo + ")!";
}

void checkOverlapped(const world_t &world)
{

    for (unsigned int i = 0; i < world.numCreatures - 1; i++)
    {
        const creature_t &firstCreature = world.creatures[i];
        for (unsigned int j = i + 1; j < world.numCreatures; j++)
        {
            const creature_t &secondCreature = world.creatures[j];
            if (firstCreature.location.r == secondCreature.location.r &&
                firstCreature.location.c == secondCreature.location.c)
            {
                string errorInfo = renderOverlappedInfo(firstCreature, secondCreature);
                Error error(CreatureOverlap, errorInfo);
                throw error;
            }
        }
    }
}

void checkProgramArg(int argc, char *argv[])
{
    checkArgc(argc);
    checkRoundsNum(atoi(argv[3]));
}

void runRounds(world_t &world, const DataForInit &dataForInit)
{
    for (int roundCount = 1; roundCount <= dataForInit.roundsNum; roundCount++)
    {
        cout << "Round " << roundCount << endl;
        for (unsigned int i = 0; i < world.numCreatures; i++)
        {
            oneCreatureAct(i, world, dataForInit.outputMode);
        }
        if (dataForInit.outputMode == Concise)
            viewGrid(world);
    }
}

void viewInitState(const world_t &world)
{
    cout << "Initial state" << endl;
    viewGrid(world);
}

DataForInit::DataForInit(int argc, char *argv[])
    : speciesSummary(argv[1]),
      worldFile(argv[2]),
      roundsNum(atoi(argv[3])),
      outputMode(Concise)
{
    if (argc > 4)
    {
        string verboseSpecifier(argv[4]);
        if (verboseSpecifier == "v" || verboseSpecifier == "verbose")
            outputMode = Verbose;
    }
}