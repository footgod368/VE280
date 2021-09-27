//for test
#include <iostream>
using namespace std;
//function overload
int square(int a)
{
    return a*a;
}
double square(double a)
{
    return a*a;
}

int main()
{
    int x = 2;
    double y = 1.1;
    cout << "x^2 = " << square(x) << endl;
    cout << "y^2 = " << square(y) << endl;
    return 0;
}