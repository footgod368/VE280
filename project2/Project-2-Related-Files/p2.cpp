#include <iostream>
#include "recursive.h"
#include "p2.h"
using namespace std;

int size(list_t list)
{
    if (list_isEmpty(list)) return 0;
    else return 1+size(list_rest(list));
}

int sum(list_t list)
{
    if (list_isEmpty(list)) return 0;
    else return list_first(list)+sum(list_rest(list));
}

int product(list_t list)
{
    if (list_isEmpty(list)) return 1;
    else return list_first(list)*product(list_rest(list));
}

int accumulate(list_t list, int (*fn) (int,int), int base)
{
    if (list_isEmpty(list)) return base;
    else return fn(list_first(list),accumulate(list_rest(list),fn,base));
}

static list_t my_list_make(list_t list1, list_t list2)
{
    return list_make(list_first(list2),list1);
}

static list_t foldL(list_t list1,list_t list2)
{
    if (list_isEmpty(list2)) return list_make();
    else return foldL(my_list_make(list1,list2),list_rest(list2));
}

list_t reverse(list_t list)
{
    return foldL(list_make(),list);
}

list_t append(list_t first, list_t second)
{
    return foldL(reverse(first),second);
}

static int add(int a, int b)
{
    return a+b;
}

int main()
{
    list_t L0 = list_make();
    list_t L1 = list_make(1,L0);
    list_t L2 = list_make(2,L1);
    list_t L3 = list_make(3,L2);
    list_t L4 = list_make(4,L3);
    cout << size(L4) << endl;
    cout << sum(L4) << endl;
    cout << product(L4) << endl;
    cout << accumulate(L4,add,0) << endl;
    list_print(reverse(L4));
    cout << endl;
    list_print(append(L4,L3));
    return 0;
}