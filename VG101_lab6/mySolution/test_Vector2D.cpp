#include <iostream>
#include "Vector2D.h"
using namespace std;

int main()
{
    Vector2D<double> v0;
    v0.print();
    Vector2D<double> v(1.0, 2.0);
    v.print();

    v0 += v;
    v0.print();

    v0 -= (v * 2);
    v0.print();

    v0 *= 3.1;
    v0.print();

    v0 /= 2.0;
    v0.print();

    v0 = v;
    v0.print();

    v0 = v0;
    v0.print();

    v0 = {1.0, 3.0};
    v0.print();
    return 0;
}