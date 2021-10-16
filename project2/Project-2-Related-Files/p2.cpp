#include <iostream>
#include "recursive.h"
#include "p2.h"
using namespace std;


//list

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
//REQUIERS: list2 is non-empty
//EFFECTS: append the first element of list2 to list1
{
    return list_make(list_first(list2),list1);
}

static list_t foldL(list_t list1,list_t list2)
//EFFECTS: append each element of list2 to list1 one by one
{
    if (list_isEmpty(list2)) return list1;
    else return foldL(my_list_make(list1,list2),list_rest(list2));
}

static list_t my_list_make(list_t list1, list_t list2, bool (*judge) (int))
//overloaded my_list_make with filter
//EFFECTS: append the first element of list2 that satisfies 'judge' to list1
{
    if (list_isEmpty(list2)) return list1;
    if (!judge(list_first(list2))) return list1;
    else return list_make(list_first(list2),list1);
}

static list_t foldL(list_t list1,list_t list2, bool (*judge) (int))
//overloaded foldL with filter
//EFFECTS: append each element of list2 that satisfies 'judge' to list1
{
    if (list_isEmpty(list2)) return list1;
    else return foldL(my_list_make(list1,list2,judge),list_rest(list2),judge);
}

list_t reverse(list_t list)
{
    return foldL(list_make(),list);
}

list_t append(list_t first, list_t second)
{
    return foldL(second,reverse(first));
}

static bool isOdd(int a)
{
    return a%2!=0;
}

static bool isEven(int a)
{
    return a%2==0;
}

list_t filter(list_t list, bool (*fn) (int))
{
    return reverse(foldL(list_make(),list,fn));
}

list_t filter_odd(list_t list)
{
    return filter(list,isOdd);
}

list_t filter_even(list_t list)
{
    return filter(list,isEven);
}

static list_t foldL(list_t list1,list_t list2,int n)
//REQUIERS: n is non-negative and not greater than the size of list2
//EFFECTS: append the first n elements of list2 to list1 one by one
{
    if (n<=0) return list1;
    else return foldL(my_list_make(list1,list2),list_rest(list2),n-1);
}

static list_t head(list_t list,int n)
//REQUIERS: n is non-negative and not greater than the size of list
//EFFECTS: take the first n elements of list
{
    return reverse(foldL(list_make(),list,n));
}

static list_t tail(list_t list,int n)
//REQUIERS: n is non-negative and not greater than the size of list
//EFFECTS: take the last n elements of list
{
    return reverse(head(reverse(list),n));
}

list_t chop(list_t list,unsigned int n)
{
    if (n==0) return list;
    return head(list,size(list) - (int)n);
}

list_t insert_list(list_t first, list_t second, unsigned int n)
{
    return append(head(first,(int)n),append(second,tail(first,size(first)-(int)n)));
}


//binary tree

list_t traversal(tree_t tree)
{
    return inOrderTraversal(list_make(), tree);
}

static list_t inOrderTraversal(list_t list, tree_t tree)
{
    if (tree_isEmpty(tree)) return list;
    list=inOrderTraversal(list,tree_left(tree));
    list=list_make(tree_elt(tree),list);
    list=inOrderTraversal(list,tree_right(tree));
    return list;
}







// below is for testing
/*static int add(int a, int b)
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
    list_print(L4);
    cout << endl;
    cout << size(L4) << endl;
    cout << sum(L4) << endl;
    cout << product(L4) << endl;
    cout << accumulate(L4,add,0) << endl;
    list_print(reverse(L4));
    cout << endl;
    list_print(append(L4,L3));
    cout << endl;
    list_print(filter(L4,isEven));
    cout << endl;
    list_print(filter_even(L4));
    cout << endl;
    list_print(filter_odd(L4));
    cout << endl;
    list_print(head(L4,2));
    cout << endl;
    list_print(tail(L4,2));
    cout << endl;
   list_print(chop(L4,2));
    cout << endl;
   list_print(insert_list(L4,L3,2));
    cout << endl;
    return 0;
}*/