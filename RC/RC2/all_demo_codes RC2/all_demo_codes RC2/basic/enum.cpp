#include<iostream>
using namespace std;

enum color{r=1, g=3, b} c;
int main()
{

    c = r;
    cout << c << endl;

    c = g;
    cout << c << endl;

    c = b;
    cout << c << endl;

    color d = c;
    cout <<d << endl;
}

