#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int a;
    double b;
    char c;
    // ofstream fout("data.txt");
    // fout<<1<<' '<<1.2<<' '<<'D';
    ifstream fin("data.txt");
    cout << a << endl << b << endl << c;
    return 0;

}
//note that do not fout("data.txt") and fin("data.txt") at the same time