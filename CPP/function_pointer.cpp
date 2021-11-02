#include <iostream>

using namespace std;

int max(int a, int b)
{
    return a > b ? a : b;
}

int min(int a, int b)
{   
    int result = a < b ? a : b;
    return result;
}

int extremum(int arr[], int size, int (*maxOrMin)(int, int))
{
    if (size == 1)
        return arr[0];
    else
        return maxOrMin(arr[0], extremum(arr + 1, size - 1, maxOrMin));
}

int main()
{
    int arr[5] = {2, 4, 6, 8, 10};
    cout << extremum(arr, 5, max) << endl
         << extremum(arr, 5, min) << endl;
    return 0;
}