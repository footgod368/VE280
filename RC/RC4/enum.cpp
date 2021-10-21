#include <iostream>

enum A {
    a, b, c=-1, d, e=5, f, g=a + e, h
};

int main() {
    //std::cout << a << ' ' << b << ' ' << c << ' ' << d << ' ' << e << ' ' << f << ' ' << g << ' ' << h << '\n';
    A A1 = A::a;
    std::cout << static_cast<int>(A1) << '\n';
}
