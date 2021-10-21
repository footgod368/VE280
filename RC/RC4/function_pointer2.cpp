#include <iostream>

int fi_se(int a, int b, int (*fp)(int, int)) {
    return fp(a, b);
}

int fi(int a, int b) {
    return a;
}

int se(int a, int b) {
    return b;
}

int main() {
    std::cout << fi_se(2, 3, fi) << '\n' << fi_se(2, 3, se) << '\n';
}
