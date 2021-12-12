#include <iostream>
#include <cassert>
#include <cstdlib>
#include "dlist.h"
using namespace std;

enum InputType
{
    INTEGER,
    COMMAND,
    ERROR_1,
    ERROR_2,
    ERROR_3,
    EXIT
};

struct Input
{
    string str;
    InputType type;
};

class Calculator
{
private:
    Dlist<int> *stack;
    int operandsNum;
    Input input;
    void handleInteger();
    void handleCommand();
    void doArithmetic(int (*fp)(int, int));
    void negate();
    void duplicate();
    void reverse();
    void print();
    void clear();
    void printAll();
    void quit();

public:
    Calculator();
    ~Calculator();
    void read();
    void distinguishInput();
    void handleInput();
};

int main()
{
    Calculator calculator;
    try
    {
        while (true)
        {
            try
            {
                calculator.read();
                calculator.distinguishInput();
                calculator.handleInput();
            }
            catch (InputType errorType)
            {
                if (errorType == EXIT)
                    throw EXIT;
                if (errorType == ERROR_1)
                    cout << "Bad input\n";
                if (errorType == ERROR_2)
                    cout << "Not enough operands\n";
                if (errorType == ERROR_3)
                    cout << "Divide by zero\n";
                continue;
            }
        }
    }
    catch (InputType exit)
    {
    }
    return 0;
}

Calculator::Calculator()
    : stack(new Dlist<int>),
      operandsNum(0),
      input({"", INTEGER}) {}

Calculator::~Calculator()
{
    delete stack;
}

void Calculator::read()
{
    input = {"", ERROR_1};
    cin >> input.str;
    if (!cin)
        throw ERROR_1;
}

bool isPosInt(string str)
{
    for (unsigned i = 0; i <= str.length() - 1; i++)
    {
        if (str[i] < '0' || str[i] > '9')
            return false;
    }
    return true;
}

bool isNegInt(string str)
{
    if (str.length() < 2 || str[0] != '-')
        return false;
    return isPosInt(str.substr(1));
}

bool isInteger(string str)
{
    return !str.empty() && (isPosInt(str) || isNegInt(str));
}

bool isCommand(string str)
{
    if (str.length() != 1)
        return false;
    char ch = str[0];
    string commands = "+-*/ndrpcaq";
    return commands.find(ch) != string::npos;
}

void Calculator::distinguishInput()
{
    if (isInteger(input.str))
        input.type = INTEGER;
    else if (isCommand(input.str))
        input.type = COMMAND;
    else
        throw ERROR_1;
}

void Calculator::handleInput()
{
    if (input.type == INTEGER)
        handleInteger();
    else if (input.type == COMMAND)
        handleCommand();
    else
        assert(0);
}

void Calculator::handleInteger()
{
    int *integer = new int(stoi(input.str));
    stack->insertFront(integer);
    operandsNum++;
}

int add(int a, int b)
{
    return a + b;
}

int subtract(int a, int b)
{
    return a - b;
}

int multiple(int a, int b)
{
    return a * b;
}

int divide(int a, int b)
{
    return a / b;
}

void Calculator::handleCommand()
{
    switch (input.str[0])
    {
    case '+':
        doArithmetic(add);
        break;
    case '-':
        doArithmetic(subtract);
        break;
    case '*':
        doArithmetic(multiple);
        break;
    case '/':
        doArithmetic(divide);
        break;
    case 'n':
        negate();
        break;
    case 'd':
        duplicate();
        break;
    case 'r':
        reverse();
        break;
    case 'p':
        print();
        break;
    case 'c':
        clear();
        break;
    case 'a':
        printAll();
        break;
    case 'q':
        quit();
        break;
    default:
        assert(0);
        break;
    }
}

void Calculator::doArithmetic(int (*fp)(int, int))
{
    if (operandsNum < 2)
        throw ERROR_2;
    int *operand_1 = stack->removeFront();
    int *operand_2 = stack->removeFront();
    if (fp == divide && *operand_1 == 0)
    {
        stack->insertFront(operand_2);
        stack->insertFront(operand_1);
        throw ERROR_3;
    }
    int *result = new int(fp(*operand_2, *operand_1));
    delete operand_1;
    delete operand_2;
    stack->insertFront(result);
    operandsNum--;
}

void Calculator::negate()
{
    if (operandsNum < 1)
        throw ERROR_2;
    int *operand = stack->removeFront();
    int *result = new int((-1) * (*operand));
    delete operand;
    stack->insertFront(result);
}

void Calculator::duplicate()
{
    if (operandsNum < 1)
        throw ERROR_2;
    int *operand = stack->removeFront();
    int *result_1 = new int(*operand);
    int *result_2 = new int(*operand);
    delete operand;
    stack->insertFront(result_1);
    stack->insertFront(result_2);
    operandsNum++;
}

void Calculator::reverse()
{
    if (operandsNum < 2)
        throw ERROR_2;
    int *operand_1 = stack->removeFront();
    int *operand_2 = stack->removeFront();
    stack->insertFront(operand_1);
    stack->insertFront(operand_2);
}

void Calculator::print()
{
    if (operandsNum < 1)
        throw ERROR_2;
    int *operand = stack->removeFront();
    cout << (*operand) << "\n";
    stack->insertFront(operand);
}

void Calculator::clear()
{
    while (operandsNum > 0)
    {
        int *victim = stack->removeFront();
        delete victim;
        operandsNum--;
    }
}

void Calculator::printAll()
{
    if (operandsNum == 0)
    {
        cout << "\n";
        return;
    }
    int *top = stack->removeFront();
    cout << (*top) << " ";
    operandsNum--;
    printAll();
    stack->insertFront(top);
    operandsNum++;
}

void Calculator::quit()
{
    throw EXIT;
}