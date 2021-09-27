#include <iostream>
#include <string>
using namespace std;

void reverse(string & str)
{
    if (str.empty()) return;
    unsigned l_str = str.size();
    string rev(l_str,'a'); //note that rev has to be well initialized, so that we can use rev[i] later!
    for(unsigned i=0;i<=l_str-1;i++)
    {
        rev[i] = str[l_str - 1 - i];
    }
    str = rev;
    return;
}

int main()
{
    string str;
    getline(cin,str);
    reverse(str);
    cout << str << endl;
    return 0;    
}