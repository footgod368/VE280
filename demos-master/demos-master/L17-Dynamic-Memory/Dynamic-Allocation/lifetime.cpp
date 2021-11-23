#include <iostream>
using namespace std;

int *p2 = NULL;

void no_delete()
{
    int *p1 = new int(5);
    p2 = p1;
}

int main()
{
    no_delete();
    cout << *p2 << endl; // 5
    return 0;
}