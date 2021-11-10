//
// Created by makersmelx on 2021/6/21.
//
#include "plugin.h"
#include <iostream>
#include <sstream>
#include <regex>

class Add : public Plugin
{
public:
    Add() : Plugin()
    {
        this->name = "add";
        this->author = "Bole";
        this->description = "add two integers";
        this->help = "Type \"simple\" in the program. It will show one message.";
    }

    string response(const string &str) const override
    {
        istringstream iss(str);
        string command;
        iss >> command;
        int n1 = 0, n2 = 0;
        iss >> n1 >> n2;
        return to_string(n1 + n2);
    }

    int matchRule(const string &str) const override
    {
        return (str.substr(0, 4) == "add ");
    }

    string toString() const override
    {
        string output = "Name: " + this->name + "\n" + "Author: " + this->author + "\n" + "Description: " + this->description + "\n" + "Help: " + this->help;
        return output;
    }
};

extern "C" Plugin *create()
{
    return new Add;
}

extern "C" int *destroy(Plugin *p)
{
    delete p;
    return 0;
}