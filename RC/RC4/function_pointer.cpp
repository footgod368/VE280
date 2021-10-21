#include <iostream>

int fi(int x, int y) {
    return x;
}

int se(int x, int y) {
    return y;
}

int sum(int x, int y) {
    return x + y;
}

int sum3(int x, int y, int z=0) {
    return x + y + z;
}

int sum2(int x, int y=0) {
    return x + y;
}

int main() {
    int (*f)(int, int b);
    f = fi;
    std::cout << f(2, 3) << '\n';
    f = &se;
    std::cout << f(2,3) << '\n';
    f = sum;
    std::cout << (*f)(2, 3) << '\n';
    f = sum2;
    std::cout << f(2,3) << '\n';
    //std::cout << f(4) << '\n';
    //f = sum3;
    std::cout << f(1, 2) << '\n';
    int (*const g)(int, int) = sum;
    //g = fi;
    std::cout << g(1,2) << '\n';
}
