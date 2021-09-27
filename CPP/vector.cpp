#include <iostream>
#include <string> //remember to include string
#include <vector> //remember to include vector
using namespace std;
int main()
{
    vector<string> v_str;//"vector<string>" is a class (type), v_str is an object (variable)
    string str;
    cout<<">";
    getline(cin,str); // getline(in_stream,string) to get one line from in_stream into string
    while (str!="exit")
    {
        v_str.push_back(str); //use vector.pushback(new_element) to append new elements to a vector
        cout<<">";
        getline(cin,str);
    }
    for (unsigned i=0;i<v_str.size();i++) //remember to use "unsigned" type in loops, since vector.size() returns unsigned values
    {
        cout<<v_str[i]<<endl;
    }
    return 0;    
}