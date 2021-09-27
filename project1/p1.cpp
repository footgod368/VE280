#include <iostream>
#include <string>
#include <cmath>
using namespace std;

//print "Pass\n" if ture, "Fail\n" if false
void print_result(bool judge);

//judge whether target is triangle number
bool triangle(const int & target);

//judge whether target is power number
bool power(const int & target);

//judge whether target is sum of consecutive squares
bool squares(const int & target);

//judge whether target is abundant number
bool abundant(const int & target);


int main()
{   
    int target, option;
    while(1)
    {
        cout << "Please enter the integer and the test choice: " << endl;
        cin >> target >> option;
        if (target>0 && target<=10000000 && option>=1 && option <=4)
        break;
    }
    switch (option)
    {
    case 1:
        print_result(triangle(target));
        break;
    case 2:
        print_result(power(target));
        break;
    case 3:
        print_result(squares(target));
        break;
    case 4:
        print_result(abundant(target));
        break;
    default:
        break;
    }
    return 0;
}

void print_result(bool judge)
{
    if (judge)
    cout << "Pass\n";
    else
    cout << "Fail\n";
}

bool triangle(const int & target)
{
    return true;
}

bool power(const int & target)
{
    return true;
}

bool squares(const int & target)
{
    return true;
}

bool abundant(const int & target)
{
    return true;
}