#include <iostream>
#include "dlist.h"
#include <cassert>

using namespace std;

void test_copy(Dlist<int> l)
{
    int *ip = new int(1);
    l.insertFront(ip);
}

int main()
{
    int result = 0;

    Dlist<int> ilist;
    int *ip = new int(1);
    ilist.insertFront(ip);

    // Now ilist should be (1)

    // test removing from a list of size one.
    ip = ilist.removeFront();
    // if(*ip != 1)
    //     result = -1;
    assert(*ip == 1);
    delete ip;

    assert(ilist.isEmpty());

    // Now ilist should be ()

    ip = new int(4);
    ilist.insertFront(ip);

    // Now ilist should be (4)

    ip = new int(5);
    ilist.insertBack(ip);

    // Now ilist should be (4 5)

    ip = new int(3);
    ilist.insertFront(ip);

    // Now ilist should be (3 4 5)

    ip = new int(2);
    ilist.insertFront(ip);

    // Now ilist should be (2 3 4 5)

    ip = new int(6);
    ilist.insertBack(ip);

    // Now ilist should be (2 3 4 5 6)

    ip = new int(7);
    ilist.insertBack(ip);

    // Now ilist should be (2 3 4 5 6 7)

    ip = ilist.removeFront();
    assert(*ip == 2);
    delete ip;

    assert(!ilist.isEmpty());

    // Now ilist should be (3 4 5 6 7)

    ip = ilist.removeBack();
    assert(*ip == 7);
    delete ip;

    assert(!ilist.isEmpty());

    // Now ilist should be (3 4 5 6)

    ip = new int(7);
    ilist.insertBack(ip);

    // Now ilist should be (3 4 5 6 7)

    ip = ilist.removeFront();
    assert(*ip == 3);
    delete ip;

    assert(!ilist.isEmpty());

    // Now ilist should be (4 5 6 7)

    ip = ilist.removeFront();
    assert(*ip == 4);
    delete ip;

    assert(!ilist.isEmpty());

    // Now ilist should be (5 6 7)

    ip = ilist.removeBack();
    assert(*ip == 7);
    delete ip;

    assert(!ilist.isEmpty());

    // Now ilist should be (5 6)

    ip = ilist.removeBack();
    assert(*ip == 6);
    delete ip;
    assert(!ilist.isEmpty());

    // Now ilist should be (5)

    ip = ilist.removeBack();
    assert(*ip == 5);
    delete ip;

    assert(ilist.isEmpty());

    // Now ilist should be ()

    ip = new int(4);
    ilist.insertFront(ip);

    // Now ilist should be (4)

    ip = new int(5);
    ilist.insertBack(ip);

    // Now ilist should be (4 5)

    ip = new int(3);
    ilist.insertFront(ip);

    // Now ilist should be (3 4 5)

    test_copy(ilist);
    Dlist<int> ilist_copy(ilist);

    ip = ilist_copy.removeBack();
    assert(*ip == 5);
    delete ip;

    // Now ilist_copy should be (3 4)

    assert(!ilist_copy.isEmpty());

    ip = ilist_copy.removeFront();
    assert(*ip == 3);
    delete ip;

    // Now ilist_copy should be (4)

    assert(!ilist_copy.isEmpty());

    ip = ilist_copy.removeFront();
    assert(*ip == 4);
    delete ip;

    // Now ilist_copy should be ()

    assert(ilist_copy.isEmpty());
    try
    {
        int *ip = ilist_copy.removeFront();
    }
    catch (emptyList e)
    {
    }

    Dlist<int> ilist_assign;
    ilist_assign = ilist;
    Dlist<int> ilist_assign2;
    ilist_assign2 = ilist;

    ip = ilist_assign.removeBack();
    assert(*ip == 5);
    delete ip;
    ip = ilist_assign.removeFront();
    assert(*ip == 3);
    delete ip;
    ip = ilist_assign.removeBack();
    assert(*ip == 4);
    delete ip;

    ip = ilist_assign2.removeBack();
    assert(*ip == 5);
    delete ip;
    ip = ilist_assign2.removeFront();
    assert(*ip == 3);
    delete ip;
    ip = ilist_assign2.removeBack();
    assert(*ip == 4);
    delete ip;

    return 0;
}
