#include <iostream>
#include <cassert>
#include <cstdlib>
#include "dlist.h"
using namespace std;

enum Status
{
    PLATINUM,
    GOLD,
    SILVER,
    REGULAR
};
const string statusToStr[4] = {"platinum", "gold", "silver", "regular"};
Status strToStatus(string str)
{
    for (int i = 0; i <= 3; i++)
    {
        if (statusToStr[i] == str)
            return (Status)i;
    }
    assert(0);
    return (Status)0;
}

struct Call
{
    int tick;
    string name;
    Status status;
    int duration;
};

class CallQueue
{
private:
    Dlist<Call> *queue;
    int callsNum;

public:
    CallQueue();
    ~CallQueue();
    int size();
    bool isEmpty();
    void enqueue(Call *newCall);
    void dequeue();
    Call *front();
};

class Agent
{
private:
    int busyDuration;
    Call *currentServingCall;
    int finishedNum;

public:
    Agent();
    ~Agent();
    void actOnTick(int currentTick, CallQueue *fourQueues[4]);
    bool isBusy();
    int getFinishedNum();
};

class Controller
{
private:
    int currentTick;
    int callsNum;

    CallQueue *platinumQueue;
    CallQueue *goldQueue;
    CallQueue *silverQueue;
    CallQueue *regularQueue;
    CallQueue *fourQueues[4];

    CallQueue *allCallsQueue;

    Agent *agent;

    void announceCalls();
    void placeCalls();

public:
    Controller();
    ~Controller();
    void readFile();
    void runNewTick();
    bool shouldStop();
};

int main()
{
    Controller *controller = new Controller;
    controller->readFile();
    while (!controller->shouldStop())
    {
        controller->runNewTick();
    }
    delete controller;
    return 0;
}

int CallQueue::size()
{
    return callsNum;
}

bool CallQueue::isEmpty()
{
    return callsNum == 0;
}

void CallQueue::enqueue(Call *newCall)
{
    queue->insertBack(newCall);
    callsNum++;
}

void CallQueue::dequeue()
{
    Call *victim = queue->removeFront();
    delete victim;
    callsNum--;
}

Call *CallQueue::front()
{
    Call *result = queue->removeFront();
    queue->insertFront(result);
    return result;
}

Agent::Agent()
    : busyDuration(0),
      currentServingCall(new Call),
      finishedNum(0) {}

Agent::~Agent()
{
    delete currentServingCall;
}

void Agent::actOnTick(int currentTick, CallQueue *fourQueues[4])
{

    busyDuration--;
    if (isBusy())
        return;

    for (int i = 0; i <= 3; i++)
    {

        if (!fourQueues[i]->isEmpty() && fourQueues[i]->front()->tick <= currentTick)
        {
            Call *thisCall = fourQueues[i]->front();
            *currentServingCall = *thisCall;
            fourQueues[i]->dequeue();
            cout << "Answering call from " << currentServingCall->name << "\n";
            busyDuration = currentServingCall->duration;
            finishedNum++;
            break;
        }
    }
}

int Agent::getFinishedNum()
{
    return finishedNum;
}

bool Agent::isBusy()
{
    return busyDuration > 0;
}

CallQueue::CallQueue()
    : queue(new Dlist<Call>),
      callsNum(0) {}

CallQueue::~CallQueue()
{
    delete queue;
}

Controller::Controller()
    : currentTick(0),
      callsNum(0),
      platinumQueue(new CallQueue),
      goldQueue(new CallQueue),
      silverQueue(new CallQueue),
      regularQueue(new CallQueue),
      fourQueues{platinumQueue, goldQueue, silverQueue, regularQueue},
      allCallsQueue(new CallQueue),
      agent(new Agent) {}

Controller::~Controller()
{
    delete platinumQueue;
    delete goldQueue;
    delete silverQueue;
    delete regularQueue;
    delete allCallsQueue;
    delete agent;
}

string getOneWord(string &str)
{
    unsigned start, end;
    for (unsigned i = 0; i < str.length(); i++)
    {
        if (str[i] != ' ')
        {
            start = i;
            break;
        }
    }
    for (unsigned i = start; i < str.length(); i++)
    {
        if (str[i] == ' ' || i == str.length() - 1)
        {
            end = i;
            break;
        }
    }
    string result = str.substr(start, end - start);
    str = str.substr(end);
    return result;
}

void Controller::readFile()
{
    cin >> callsNum;
    string line;
    getline(cin, line);
    while (getline(cin, line))
    {
        line = line + " ";
        Call newCall;
        newCall.tick = stoi(getOneWord(line));
        newCall.name = getOneWord(line);
        newCall.status = strToStatus(getOneWord(line));
        newCall.duration = stoi(getOneWord(line));
        fourQueues[newCall.status]->enqueue(new Call(newCall));
        allCallsQueue->enqueue(new Call(newCall));
    }
}

void Controller::runNewTick()
{
    cout << "Starting tick #" << currentTick << "\n";

    announceCalls();

    agent->actOnTick(currentTick, fourQueues);

    currentTick++;
}

void Controller::announceCalls()
{
    while (!allCallsQueue->isEmpty() && allCallsQueue->front()->tick == currentTick)
    {
        Call *thisCall = allCallsQueue->front();
        cout << "Call from " << thisCall->name << " a " << statusToStr[thisCall->status] << " member\n";
        allCallsQueue->dequeue();
    }
}

bool Controller::shouldStop()
{
    return callsNum == agent->getFinishedNum() && !agent->isBusy();
}
