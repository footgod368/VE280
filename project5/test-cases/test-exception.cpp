#include <iostream>
#include "dlist.h"

using namespace std;

int main()
{
    Dlist<int> ilist;
    try
    {
        int *ip = ilist.removeFront();
    }
    catch (emptyList e)
    {
        cout << "Exception" << endl;
    }
    return 0;
}