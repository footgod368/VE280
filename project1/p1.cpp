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

//helper function used in squares()
int square_sum(const int & m, const int & i);

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
    double limit = sqrt(2*target);
    for (int n=1; n<limit; n++)
    {
        if (n*(n+1) == 2*target)
            return true;
    }
    return false;
}

bool power(const int & target)
{
    if (target == 1) 
        return true;

    bool judge = false;
    int n = 2;
    while (1)
    {
        if (pow(2,n) > target)
            break;

        for (int m=2; pow(m,n)<=target; m++)
        {
            if (pow(m,n) == target)
            {
                judge = true;
                break;
            }
        }
        n++;
    }
    
    return judge;
}

bool squares(const int & target)
{
    bool judge = false;
    for (int m=1; m*m <= target; m++)
    {
        for (int i=0; (m+i)*(m+i)<=target; i++)
        {
            if (square_sum(m,i) == target)
            {
                judge = true;
                break;
            }
        }

        if (judge == true)
            break;
    }
    return judge;
}

bool abundant(const int & target)
{
    int factors_sum = 0;
    for (int i=1; i<target; i++)
    {
        if (target%i == 0)
            factors_sum += i;
    }
    return factors_sum>target;
}

int square_sum(const int & m, const int & i)
{
    int sum = 0;
    for (int k=0; k<=i; k++)
        sum += (m+k)*(m+k);
    return sum;
}