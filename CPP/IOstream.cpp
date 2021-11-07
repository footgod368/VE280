#include <iostream>
#include <iomanip> // setw(int n)
#include <fstream>
using namespace std;

int main()
{
    //output stream:
    int a = 12;
    int b = 188;
    int c = 1999;
    int d = 200000;
    cout << to_string(a) << setw(5) << b << c << setw(5) << d << endl; //setw(int n)只规定紧跟着它的那个数的右对齐宽度，不足n补空格
    cerr << "Error messages" << endl;                                  // basically the same as cout, but usually used for error messages

    //input streams:
    cin >> a; //type "19 this string\n"
              //19 is extracted into a, " this string\n" is still in buffer
    string str;
    cin.get();         //get a single character from buffer, cin.get(bar) bar will be " ", also cin.get()
    getline(cin, str); //str is "this string", no \n
    cout << a << endl;
    cout << str << endl;

    //failed input streams:
    if (cin >> a) //type "42abc\n"
        cout << "success" << endl;
    // a will be 42, while "abc\n" is still in buffer
    cout << a;       //42
    if (!(cin >> a)) //"abc\n" in buffer, will failed
        cout << "failed" << endl;
    cout << a; //0

    /*
    //file streams:
    ofstream fout;                   //ofstream is a type, fout is an object
    fout.open("test.txt");           // connect fout to a file, can also use constructor directly when declaring
    fout << "line1\nline2\nline3\n"; // use insertion operator
    fout.close();                    //recommended to close file after using fstream

    ifstream fin_fail("a.txt"); //use constructor, "a.txt" doesn't exist
    if (!fin_fail)              //judge the state of fin
    {
        cerr << "cannot open file\n";
        //return -1;
    }

    ifstream fin;
    string line;

     fin.open("test.txt");
    while (fin) //correct way of reading file line by line
    {
        getline(fin, line);
        if (fin) //avoid the last blank line
            cout << line << endl;
    }
    fin.close();
    line = "";
    

    fin.open("test.txt");
    while (getline(fin, line)) //another easy and correct way of reading file line by line
    //get line will return a reference of fin after its impact
    {
        cout << line << endl;
    }
    fin.close();
    */
}