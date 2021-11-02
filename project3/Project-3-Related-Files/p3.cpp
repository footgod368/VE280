#include <iostream>
#include <cstdlib>
#include <string>
#include "world_type.h"
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    /*
    Handle program arguments
    */
    try
    {
        checkArgc(argc);
    }
    catch (...)
    {
        return 0;
    }
    string speciesSummary(argv[1]);
    string worldFile(argv[2]);
    int roundsNum = atoi(argv[3]);
    try
    {
        checkRoundsNum(roundsNum);
    }
    catch (...)
    {
        return 0;
    }
    OutputMode outputMode = Concise;
    if (argc > 4)
    {
        string verboseSpecifier(argv[4]);
        if (verboseSpecifier == "v" || verboseSpecifier == "verbose")
            outputMode = Verbose;
    }
    /*
    Initialize the world
    */
    world_t world;
    try
    {
        initWorld(speciesSummary, worldFile, world);
    }
    catch (...)
    {
        return 0;
    }
    cout << "Initial state" << endl;
    viewGrid(world);
    /*
    Run rounds
    */
    for (int roundCount = 1; roundCount <= roundsNum; roundCount++)
    {
        cout << "Round " << roundCount << endl;
        for (unsigned int i = 0; i < world.numCreatures; i++)
        {
            oneCreatureAct(i, world, outputMode);
        }
        if (outputMode == Concise)
            viewGrid(world);
    }

    return 0;
}