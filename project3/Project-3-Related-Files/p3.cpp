#include <iostream>
#include <cstdlib>
#include <string>
#include "world_type.h"
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    string speciesSummary(argv[1]);
    string worldFile(argv[2]);
    string verboseSpecifier(argv[4]);
    int roundsNum = atoi(argv[3]);
    OutputMode outputMode = Concise;
    if (verboseSpecifier == "v" || verboseSpecifier == "verbose")
        outputMode = Verbose;

    world_t world = initWorld(speciesSummary, worldFile);

    for (int roundCount = 1; roundCount <= roundsNum; roundCount++)
    {
        cout << "Round " << roundCount << endl;
        for (int i = 0; i < world.numCreatures; i++)
        {
            oneTakeAction(i, world, outputMode);
        }
    }

    // cout << roundsNum << endl
    //      << (outputMode == Verbose) << endl
    //      << world.numCreatures << endl;
    // viewGrid(world);
    // doLeft(0, world, outputMode);
    // cout << world.creatures[0].species->programSize << endl;
    // cout << opName[world.creatures[1].species->program[1].op] << endl;
    return 0;
}