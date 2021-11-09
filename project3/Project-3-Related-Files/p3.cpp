#include <iostream>
#include <cstdlib>
#include <string>
#include "world_type.h"
#include "simulation.h"

using namespace std;

int main(int argc, char *argv[])
{
    try
    {
        checkProgramArg(argc, argv);
    }
    catch (...)
    {
        return 0;
    }

    DataForInit dataForInit(argc, argv);

    world_t world;
    try
    {
        initWorld(dataForInit, world);
    }
    catch (...)
    {
        return 0;
    }

    viewInitState(world);

    runRounds(world, dataForInit);
    return 0;
}