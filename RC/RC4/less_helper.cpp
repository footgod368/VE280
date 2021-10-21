struct big_struct{
    int a[100000];
};

int g(big_struct& s, int n) {
    if (n == 0) return 0;
    return 1 + g(s, n - 1);
}

int f(big_struct s, int n) {
    return g(s, n);
    if (n == 0) return 0;
    return 1 + f(s, n - 1);
}

int main() {
    big_struct s;
    f(s, 100);
}
