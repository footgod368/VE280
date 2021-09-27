//for test
#include <iostream>
using namespace std;

// #define max(a,b) ( (a>b)?a:b )
inline double max(double a, double b)
{
    return ( (a>b)?a:b );
}

int main()
{
    cout << max(3,4);
}