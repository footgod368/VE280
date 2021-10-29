#include <iostream>
#include <fstream>
using namespace std;

int main()
{
    int a;
    double b;
    char c;
    // ofstream fout("data.txt");
    // fout << 1 << ' ' << 1.2 << ' ' << 'D';
    // fout.close();
    ifstream fin("test/data.txt");
    fin >> a >> b >> c;
    cout << a << endl
         << b << endl
         << c << endl;
    return 0;
}
//note that if fout("data.txt") and fin("data.txt") at the same time, need to close the fout at first