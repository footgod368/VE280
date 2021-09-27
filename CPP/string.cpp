//basic of C++ string class
#include <string>
#include <iostream>
using namespace std;
int main()
{
 string s1,s2;//define without initializing
 string s3="hello world!";//define with initializing
 string s4("hello world!");//another way to initialize
 s2="today";//assignment
 s1=s3+" "+s4;//directly combine strings like matlab
 s1+="8";//appending directly
 cout<<s1+s2+"!"<<endl;
 return 0;
}
