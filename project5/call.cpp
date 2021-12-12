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
Status strToStatus(const string &str)
//EFFECTS: return the corresponding Status w.r.t. a string among "platinum", "gold", "silver", "regular"
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
//OVERVIEW: contains all information of a single call
{
    int tick;
    string name;
    Status status;
    int duration;
};

class CallQueue
//OVERVIEW: a queue of calls
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
//OVERVIEW: the agent
{
private:
    int busyDuration;         //represents how many ticks are left for the agent to finish current call
    Call *currentServingCall; //represents the call which is currently served by the agent
    int finishedNum;          //represents how many calls have been finished by the agent

public:
    Agent();
    ~Agent();
    void actOnTick(const int currentTick, CallQueue *fourQueues[4]);
    //MODIFIES: *this, *fourQueues[]
    //EFFECTS: let the agent act on a certain tick, depending on whether or not the agent is busy
    //if not busy, the agent looks for the call with highest priority in 'fourQueues' that happens not later than 'currentTick' to serve
    bool isBusy();
    //EFFECTS: return true if the agent is busy, false if not
    int getFinishedNum();
    //EFFECTS: returns the 'finishedNum' of the agent
};

class Controller
{
private:
    int currentTick; //represents the current tick
    int callsNum;    // represents the total number of calls

    CallQueue *platinumQueue; //represents the queue of platinum calls
    CallQueue *goldQueue;     //represents the queue of gold calls
    CallQueue *silverQueue;   //represents the queue of silver calls
    CallQueue *regularQueue;  //represents the queue of regular calls
    CallQueue *fourQueues[4]; //the array of the four queues above

    CallQueue *allCallsQueue; //represents the queue of all calls, in the order of the input file

    Agent *agent; //represents the agent

    void announceCalls();
    //EFFECTs: announce all calls happening on current tick

public:
    Controller();
    ~Controller();
    void readFile();
    //MODIFIES: *this
    //EFFECTS: read the input file and store the information of calls
    void runNewTick();
    //MODIFIES: *this
    //EFFECTS: launch a new tick and run on it
    bool shouldStop();
    //EFFECTS: return whether the simulation should stop
};

int main()
{
    Controller controller;
    controller.readFile();
    do
    {
        controller.runNewTick();
    } while (!controller.shouldStop());
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

void Agent::actOnTick(const int currentTick, CallQueue *fourQueues[4])
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
    string line;
    getline(cin, line);
    callsNum = stoi(line);
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
