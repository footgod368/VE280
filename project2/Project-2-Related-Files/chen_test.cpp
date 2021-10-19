#include <iostream>
#include "p2.h"
#include "recursive.h"
#include <cassert>
using namespace std;

static bool list_equal(list_t l1, list_t l2)
    // EFFECTS: returns true iff l1 == l2.
{
    if(list_isEmpty(l1) && list_isEmpty(l2))
    {
        return true;
    }
    else if(list_isEmpty(l1) || list_isEmpty(l2))
    {
        return false;
    }
    else if(list_first(l1) != list_first(l2))
    {
        return false;
    }
    else
    {
        return list_equal(list_rest(l1), list_rest(l2));
    }    
}    

static bool tree_equal(tree_t t1, tree_t t2)
    // EFFECTS: returns true iff t1 == t2
{
    if(tree_isEmpty(t1) && tree_isEmpty(t2))
    {
        return true;
    }
    else if(tree_isEmpty(t1) || tree_isEmpty(t2))
    {
        return false;
    }
    else
    {
        return ((tree_elt(t1) == tree_elt(t2)) 
            && tree_equal(tree_left(t1), tree_left(t2))
            && tree_equal(tree_right(t1), tree_right(t2)));
    }
}

static int add(int a, int b)
{
    return a+b;
}

static int multiply(int a, int b)
{
    return a*b;
}

static bool greater_than_two(int a)
{
    return a>2;
}

static list_t quick_make_list(int arr[], int size){
    list_t list = list_make();
    if(size == 0){
        return list;
    }
    else{
        int i=0;
        for(i=0; i<size; i++){
            list = list_make(arr[size - 1 - i], list);
        }
        return list;
    }
}

int main(){

//list

    list_t L0 = list_make();
    list_t L1 = list_make(-1, L0);

    assert(size(L0)==0);
    assert(sum(L0)==0);
    assert(product(L0)==1);
    assert(accumulate(L0, add, 0) == 0);
    assert(accumulate(L1, add, 0) == -1);
    assert(accumulate(L0, multiply, 1) == 1);
    assert(accumulate(L1, multiply, 1) == -1);
    assert(list_equal(reverse(L0),L0));
    assert(list_equal(reverse(L1),L1));
    assert(list_equal(append(L0, L0), L0));
    assert(list_equal(append(L1, L0), L1));
    assert(list_equal(append(L0, L1), L1));
    assert(list_equal(filter_odd(L0), L0));
    assert(list_equal(filter_odd(L1), L1));
    assert(list_equal(filter_even(L0), L0));
    assert(list_equal(filter_even(L1), L0));
    assert(list_equal(filter(L0, greater_than_two), L0));
    assert(list_equal(filter(L1, greater_than_two), L0));
    assert(list_equal(insert_list(L0, L0, 0), L0));
    assert(list_equal(insert_list(L1, L0, 0), L1));
    assert(list_equal(insert_list(L0, L1, 0), L1));
    assert(list_equal(insert_list(L1, L0, 1), L1));
    assert(list_equal(chop(L0, 0), L0));
    assert(list_equal(chop(L1, 0), L1));
    assert(list_equal(chop(L1, 1), L0));

    int l2[6]={0, -5, 3, -8, 2, -22};
    int l3[6]={-22, 2, -8, 3, -5, 0};
    int l4[2]={-5, 3};
    int l5[4]={0, -8, 2, -22};
    list_t L2 = quick_make_list(l2, 6);
    list_t L3 = quick_make_list(l3, 6);
    list_t L4 = quick_make_list(l4, 2);
    list_t L5 = quick_make_list(l5, 4);

    assert(sum(L2) == -30);
    assert(size(L2) == 6);
    assert(product(L2) == 0);
    assert(accumulate(L2, add, 22) == -8);
    assert(accumulate(L2, multiply, 33) == 0);
    assert(list_equal(reverse(L2), L3));
    assert(list_equal(append(L2, L0), L2));
    assert(list_equal(filter_odd(L2), L4));
    assert(list_equal(filter_even(L2), L5));
    assert(list_equal(insert_list(L0, L2, 0), L2));
    assert(list_equal(insert_list(L2, L0, 4), L2));
    assert(list_equal(insert_list(L2, L0, 6), L2));
    assert(list_equal(insert_list(L5, L4, 1), L2));
    assert(list_equal(chop(L2, 6), L0));

    cout << "Passed list" << endl;

//tree

    tree_t T0 = tree_make();
    tree_t T1 = tree_make(-5000, T0, T0);
    tree_t T2 = tree_make(-5000, T0, T1);

    assert(tree_sum(T0) == 0);
    assert(tree_sum(T2) == -10000);
    assert(!tree_search(T0, -5000));
    assert(tree_search(T1, -5000));
    assert(tree_search(T2, -5000));
    assert(!tree_search(T2, 0));
    assert(depth(T0) == 0);
    assert(depth(T1) == 1);
    assert(depth(T2) == 2);
    assert(tree_min(T1) == -5000);
    assert(tree_min(T2) == -5000);
    assert(list_equal(traversal(T0), L0));
    assert(list_equal(traversal(T1), list_make(-5000, L0)));
    assert(list_equal(traversal(T2), list_make(-5000, list_make(-5000, L0))));
    assert(!tree_hasPathSum(T0, 0));
    assert(tree_hasPathSum(T1, -5000));
    assert(!tree_hasPathSum(T2, -5000));
    assert(tree_hasPathSum(T2, -10000));
    assert(!tree_hasPathSum(T2, 0));
    assert(covered_by(T1, T2));
    assert(!covered_by(T2, T1));
    assert(tree_equal(insert_tree(-5000, T0), T1));
    assert(tree_equal(insert_tree(-5000, T1), T2));
    assert(tree_equal(insert_tree(-5000, T2), tree_make(-5000, T0, T2)));

    cout << "Passed tree" << endl;

    return 0;
}