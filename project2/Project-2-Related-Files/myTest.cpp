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

int main()
{
//list

    list_t L0 = list_make();
    list_t L1 = list_make(1,L0);
    list_t L2 = list_make(2,L1);
    list_t L3 = list_make(3,L2);
    list_t L4 = list_make(4,L3);

    assert(size(L0) == 0);
    assert(size(L1) == 1);
    assert(size(L2) == 2);
    assert(size(L3) == 3);
    assert(size(L4) == 4);

    assert(sum(L0) == 0);
    assert(sum(L1) == 1);
    assert(sum(L2) == 3);
    assert(sum(L3) == 6);
    assert(sum(L4) == 10);

    assert(product(L0) == 1);
    assert(product(L1) == 1);
    assert(product(L2) == 2);
    assert(product(L3) == 6);
    assert(product(L4) == 24);

    assert(accumulate(L0, add, 0) == 0);
    assert(accumulate(L1, add, 0) == 1);
    assert(accumulate(L2, add, 0) == 3);
    assert(accumulate(L3, add, 0) == 6);
    assert(accumulate(L4, add, 0) == 10);

    assert(accumulate(L0, multiply, 1) == 1);
    assert(accumulate(L1, multiply, 1) == 1);
    assert(accumulate(L2, multiply, 1) == 2);
    assert(accumulate(L3, multiply, 1) == 6);
    assert(accumulate(L4, multiply, 1) == 24);

    list_t L0_rev = list_make();
    list_t L1_rev = list_make(4,L0_rev);
    list_t L2_rev = list_make(3,L1_rev);
    list_t L3_rev = list_make(2,L2_rev);
    list_t L4_rev = list_make(1,L3_rev);
    assert(list_equal(reverse(L4),L4_rev));
    assert(list_equal(reverse(L0),L0_rev));

    list_t L3_L4 = list_make(3,list_make(2,list_make(1,L4)));
    assert(list_equal(append(L3,L4), L3_L4));
    assert(list_equal(append(L3,list_make()), L3));


    list_t L4_odd = list_make(3, list_make(1,list_make()));
    list_t L4_even = list_make(4, list_make(2,list_make()));
    assert(list_equal(L4_odd, filter_odd(L4)));
    assert(list_equal(L4_even, filter_even(L4)));

    list_t L4_greater_than_two = list_make(4, list_make(3,list_make()));
    assert(list_equal(L4_greater_than_two, filter(L4, greater_than_two)));
    assert(list_equal(L0, filter(L0, greater_than_two)));

    list_t L1_L4_0 = list_make(4,list_make(3,list_make(2,list_make(1,list_make(1,list_make())))));
    list_t L3_L4_2 = list_make(3,list_make(2,L1_L4_0));
    assert(list_equal(L1_L4_0,insert_list(L1,L4,0)));
    assert(list_equal(L3_L4_2,insert_list(L3,L4,2)));

    list_t L4_chop_3 = list_make(4, list_make());
    assert(list_equal(L4_chop_3, chop(L4,3)));

    
    tree_t A = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t B = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));
    

    assert(tree_sum(A) == 7);
    assert(tree_sum(B) == 10);
    assert(tree_sum(tree_make()) == 0);

    assert(tree_search(A,1) == true);
    assert(tree_search(B,3) == true);
    assert(tree_search(tree_make(),1) == false);
    assert(tree_search(B,9) == false);

    assert(depth(tree_make()) == 0);
    assert(depth(A) == 2);
    assert(depth(B) == 3);

    assert(tree_min(A) == 1);
    assert(tree_min(B) == 1);

    assert(list_equal(traversal(B), reverse(L4)));

    assert(tree_hasPathSum(B,3));
    assert(tree_hasPathSum(B,9));
    assert(tree_hasPathSum(A,6));
    assert(!tree_hasPathSum(A,10));
    assert(!tree_hasPathSum(B,11));
    assert(!tree_hasPathSum(tree_make(),0));

    assert(covered_by(A,B));
    assert(!covered_by(tree_left(A),B));
    assert(covered_by(tree_right(A),tree_right(B)));

    assert(contained_by(tree_right(A),B));
    assert(contained_by(tree_left(A),B));
    assert(!contained_by(tree_right(B),A));
    
    assert(tree_equal(insert_tree(3,A),B));

    cout << "Passed all test cases!" << endl;

    return 0;
}