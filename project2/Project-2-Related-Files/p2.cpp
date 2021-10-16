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

static list_t inOrderTraversal(list_t list, tree_t tree)
//in order traversal of a tree
//EFFECTS: store every node of tree into list in order
{
    if (tree_isEmpty(tree)) return list;
    list=inOrderTraversal(list,tree_left(tree));
    list=list_make(tree_elt(tree),list);
    list=inOrderTraversal(list,tree_right(tree));
    return list;
}

list_t traversal(tree_t tree)
{
    return inOrderTraversal(list_make(), tree);
}

int tree_sum(tree_t tree)
{
    return sum(traversal(tree));
}

bool tree_search(tree_t tree, int key)
{
    if (tree_isEmpty(tree)) return false;
    if (tree_elt(tree)==key) return true;
    return tree_search(tree_left(tree),key)||tree_search(tree_right(tree),key);
}

static int maximum(int a, int b)
{
    return a>b?a:b;
}

int depth(tree_t tree)
{
    if (tree_isEmpty(tree)) return 0;
    return 1+maximum(depth(tree_left(tree)),depth(tree_right(tree)));
}

static int minimum(int a, int b)
{
    return a<b?a:b;
}

static int list_min(int elt, list_t list)
//REQUIERS: list is not empty
//EFFECTS: return the smallest element of list
{
    if (list_isEmpty(list)) return elt;
    return list_min(minimum(elt,list_first(list)),list_rest(list));
}

int tree_min(tree_t tree)
{
    list_t list = traversal(tree);
    return list_min(list_first(list), list);
}

static bool my_tree_hasPathSum(tree_t tree, int sum)
//EFFECTS: identical with tree_hasPathSum except that it considers the path sum of an empty tree is zero
{
    if (tree_isEmpty(tree)) return sum==0;
    return my_tree_hasPathSum(tree_left(tree), sum-tree_elt(tree)) || my_tree_hasPathSum(tree_right(tree),sum-tree_elt(tree));
}

bool tree_hasPathSum(tree_t tree, int sum)
{
    if (tree_isEmpty(tree)) return false;
    return my_tree_hasPathSum(tree,sum);
}

bool covered_by(tree_t A, tree_t B)
{
    if (tree_isEmpty(A)) return true;
    if (tree_isEmpty(B)) return false;
    return tree_elt(A)==tree_elt(B) && covered_by(tree_left(A),tree_left(B)) && covered_by(tree_right(A),tree_right(B));
}


bool contained_by(tree_t A, tree_t B)
{
    if (covered_by(A,B)) return true;
    if (tree_isEmpty(B)) return false;
    return contained_by(A,tree_left(B)) || contained_by(A,tree_right(B));
}

tree_t insert_tree(int elt, tree_t tree)
{
    if (tree_isEmpty(tree)) return tree_make(elt,tree_make(),tree_make());
    if (elt < tree_elt(tree)) return tree_make(tree_elt(tree), insert_tree(elt,tree_left(tree)), tree_right(tree));
    return tree_make(tree_elt(tree), tree_left(tree), insert_tree(elt, tree_right(tree)));
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