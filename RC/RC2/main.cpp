#include <iostream>
#include "study.h"
#include "touch_fish.h"
//must include these two header files here.

using namespace std;
int main()
{
    int option=0;
    cin >> option;
    if (option == 0)
        study();
    else
        touch_fish();
    return 0;
}