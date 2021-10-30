#include <iostream>
#include <fstream>
#include <string>

using namespace std;

int main()
{
    ofstream fout("test.sh", ios::app);
    for (int i = 0; i <= 34; i++)
    {
        string inputPath = "input/" + to_string(i) + ".in";
        ifstream fin;
        fin.open(inputPath);
        string command;
        getline(fin, command);
        fin.close();
        string outputPath = "output/" + to_string(i) + ".out";
        command += " > " + outputPath + "\n";
        fout << command;
    }
    fout.close();
    return 0;
}