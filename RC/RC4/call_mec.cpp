#include <iostream>

int output(int x, int y) {
    std::cout << x << ' ' << y << '\n';
    return 0;
}

int f(int x) {
    std::cout << x << '\n';
    return x;
}

int main () {
    output(f(1), f(2)); // the later will be evaluated first: order is not guaranteed
}
