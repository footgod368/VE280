#ifndef SIMULATION_H
#define SIMULATION_H

using namespace std;

enum OutputMode
//Overview: indicate the mode of output
{
    Verbose,
    Concise
};

struct DataForInit
//Overview: the data for initialization
{
    string speciesSummary;
    string worldFile;
    int roundsNum;
    OutputMode outputMode;

    DataForInit(int argc, char *argv[])
    {
        speciesSummary = argv[1];
        worldFile = argv[2];
        roundsNum = atoi(argv[3]);
        outputMode = Concise;
        if (argc > 4)
        {
            string verboseSpecifier(argv[4]);
            if (verboseSpecifier == "v" || verboseSpecifier == "verbose")
                outputMode = Verbose;
        }
    }
};

void readSpeciesSummary(const string &speciesSummary, string &pathOfSpecies, string speciesInfo[], int &speciesNum);
//used in 'initWorld'
//REQUIERS: 'speciesNum' is initialized to be 0;
//MODIFIES: 'pathOfSpecies', 'speciesInfo[]', 'speciesNum';
//EFFECTS: read the file whose path is 'speciesSummary'; record the first line of that file as 'pathOfSpecies';
//         record each of the rest lines in 'speciesInfo', whose size is 'speciesNum';

void readWorldFile(const string &worldFile, int &gridWidth, int &gridHeight, string creaturesInfo[], int &creaturesNum);
//used in 'initWorld'
//REQUIERS: 'creaturesNum' is initialized to be 0;
//MODIFIES: 'gridWidth', 'gridHeight', 'creaturesInfo', 'creaturesNum'
//EFFECTS:  read the file whose path is 'worldFile'; record the first line as 'gridWidth', second line as 'gridHeight';
//          record each of the rest lines in 'creatures', whose size is 'creaturesNum'

void initWorld(const DataForInit &dataForInit, world_t &world);
//MODIFIES: world
//EFFECTS:  initialize the given 'world' with the information from 'speciesSummary' and 'worldFile'

void initSpecies(const int &speciesNum, string speciesInfo[], const string &pathOfSpecies, world_t &world);
//used in 'initWorld'
//MODIFIES: 'speciesInfo[]', 'world'
//EFFECTS: initialize species of 'world'

instruction_t getInstruction(const string &line);
//EFFECTS:  get the instruction from the given 'line'

opcode_t encodeOpName(const string &nameOfOpcode);
//EFFECTS:  transform 'nameOfOpcode' into according opcode

bool isWithAddress(const opcode_t &opcode);
//EFFECTS:  judge whether the opcode is with an address

void initCreatures(const int &creaturesNum, const string creaturesInfo[], world_t &world);
//used in 'initWorld'
//MODIFIES: 'world'
//EFFECTS:  initialize creatures of 'world' according to 'creaturesNum' and 'creaturesInfo[]'

direction_t encodeDirName(const string &dirName);
//EFFECTS:  transform 'dirName' into according direction

void setSpecie(const string &specieName, creature_t &newCreature, world_t &world);
//MODIFIES: 'newCreature'
//EFFECTS:  set the species of 'newCreature' according to 'specieName'

void updateGrid(world_t &world);
//MODIFIES: 'world'
//EFFECTS:  update the grid of 'world' according to the information of creatures' locations'

creature_t *getCreatureInSquare(const int &i, const int &j, world_t &world);
//EFFECTS:  return a pointer to the creature located at' world.grid.squares[i][j]'

void viewGrid(const world_t &world);
//MODIFIES: cout
//EFFECTS:  view 'world.grid' in console

void oneCreatureAct(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature take action and update 'world' accordingly

void doHop(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature perform the instruction 'hop'

void doLeft(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature perform the instruction 'left'

void doRight(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature perform the instruction 'right'

void doInfect(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature perform the instruction 'infect'

void doIfEmpty(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature perform the instruction 'ifempty'

void doIfEnemy(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature perform the instruction 'ifenemy'

void doIfSame(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature perform the instruction 'ifsame'

void doIfWall(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature perform the instruction 'ifwall'

void doGo(const int &i, world_t &world, const OutputMode &outputMode);
//MODIFIES: world
//EFFECTS:  let the i'th creature perform the instruction 'go'

point_t sqaureFaced(const creature_t &activeCreature);
//EFFECTS: return the square faced by the creature

bool isSquareInBoundary(const point_t &square, const grid_t &grid);
//EFFECTS:  judge whether 'square' is inside the boundary of 'grid'

bool isSquareEmpty(const point_t &square, const grid_t &grid);
//REQUIERS: 'square' is inside 'grid'
//EFFECTS:  judge whether 'square' is empty

bool isFacingEnemy(const creature_t &activeCreature, const grid_t &grid);
//EFFECTS:  judge whether 'activeCreature' is facing an enemy

bool isFacingSame(const creature_t &activeCreature, const grid_t &grid);
//EFFECTS:  judge whether 'activeCreature' is facing someone of the same species

bool isLegalHop(const creature_t &activeCreature, const grid_t &grid);
//EFFECTS:  judge whether the tentative hop is legal

void checkArgc(const int &argc);
//EFFECTS:  check whether 'argc' is less than 4

void checkRoundsNum(const int &roundsNum);
//EFFECTS:  check whether 'roundsNum' is negative

void checkOverlapped(const world_t &world);
//EFFECTS:  check whether 'world' has two overlapped creatures

void checkProgramArg(int argc, char *argv[]);
//EFFECTS:  check whether program arguments are valid

void runRounds(world_t &world, const DataForInit &dataForInit);
//MODIFIES: world
//EFFECTS:  let the world start runing

void viewInitState(const world_t &world);
//EFFECTS:  print the initial state

#endif
