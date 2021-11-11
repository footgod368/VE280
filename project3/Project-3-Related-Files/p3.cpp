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
        DataForInit dataForInit(argc, argv);
        world_t world;
        initWorld(dataForInit, world);
        viewInitState(world);
        runRounds(world, dataForInit);
    }
    catch (Error error)
    {
        handleError(error);
        return 0;
    }

    return 0;
}