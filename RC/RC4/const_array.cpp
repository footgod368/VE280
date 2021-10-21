int f(int a[100000]) {
    return 0;
}

int main() {
    int a[100000]={0};
    for (int i = 0; i < 1000000; i++) {
        f(a);
    }
}
