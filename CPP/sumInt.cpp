#include <iostream>
#include <cstdlib>
using namespace std;

int main(int argc, char * argv[])
{
    int sum=0;
    for (int i=1; i<argc; i++) // argv[0] is the name of command, i.e. sumInt
    {
        sum+=atoi(argv[i]);
    }
    cout << sum <<endl;
    cout << argc << endl;
    return 0;
}