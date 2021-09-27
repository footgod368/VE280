#include <iostream>
using namespace std;

int main()
{
    int * arr = new int[1000000];
    arr[0]=1;
    cout<<arr[0];
    delete[] arr;
}