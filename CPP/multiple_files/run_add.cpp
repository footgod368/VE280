#include <iostream>
#include "add.h"
using namespace std;

int main()
{
    int x = 1;
    int y = 2;
    const int *px = &x;
    typedef int *p_int;
    const p_int py = &y;
    *py = 3;
    int *p = NULL;
    p = py;
    const int *a;
    a = py;
    const int b;
    int *const c;
    int &d;
    cout << add(*px, *p) << std::endl;
    return 0;
}