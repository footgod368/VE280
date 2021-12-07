#include <iostream>
#include "dlist.h"
#include <cassert>
using namespace std;

int main()
{
    Dlist<int> l1;
    int *n1 = new int(1);
    l1.insertFront(n1);
    int *n2 = new int(2);
    l1.insertFront(n2);
    int *n3 = new int(3);
    l1.insertBack(n3);

    int *o2 = l1.removeFront();
    assert(*o2 == 2);
    delete o2;
    int *o3 = l1.removeBack();
    assert(*o3 == 3);
    delete o3;

    Dlist<int> l2(l1);
    int *n4 = new int(4);
    l2.insertFront(n4);
    int *n5 = new int(5);
    l2.insertBack(n5);
    l2 = l1;
    l2 = l2;
    int *o1 = l2.removeBack();
    assert(*o1 == 1);
    delete o1;
    assert(l2.isEmpty());

    return 0;
}
