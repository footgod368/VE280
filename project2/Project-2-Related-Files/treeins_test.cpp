#include <iostream>
#include "recursive.h"
#include "p2.h"

using namespace std;

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


int main()
{
    tree_t start = tree_make(2,
                     tree_make(1, tree_make(), tree_make()),
                     tree_make(4, tree_make(), tree_make()));
    tree_t end = tree_make(2,
                   tree_make(1, tree_make(), tree_make()),
                   tree_make(4, 
                         tree_make(3, tree_make(), tree_make()),
                         tree_make()));

    tree_print(start);
    cout << endl;
    tree_print(end);
    cout << endl;
    list_print(traversal(end));
    cout << endl;
    cout << tree_search(end,4) << endl;
    cout << depth(start) << endl;
    cout << tree_min(end) << endl;
    cout << tree_hasPathSum(end,9) << endl;
    cout << covered_by(start,end) << endl;
    cout << covered_by(end,start) << endl;
    cout << contained_by(tree_left(start),end) << endl;
    cout << contained_by(tree_right(end),start) << endl;
    cout << contained_by(tree_left(end),start) << endl;
    
    tree_t candidate = insert_tree(3, start);
    tree_print(end);
    cout << endl;
    cout << endl;

    tree_print(candidate);
    cout << endl;

    if(tree_equal(candidate, end))
    {
        cout << "Success!\n";
        return 0;
    }
    else
    {
        cout << "Failed\n";
        return -1;
    }
}
