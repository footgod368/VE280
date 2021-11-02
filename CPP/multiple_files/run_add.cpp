#include <iostream>
#include "add.h"

int main()
{
    int x = 1;
    int const *p = &x;
    std::cout << add(*p, 6) << std::endl;
    return 0;
}