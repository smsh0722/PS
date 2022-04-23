/* smsh0722 
 * 5639
 * 이진 검색 트리
 * */
#include <iostream>
using namespace std;

struct node{
    int val;
    int l, r;
    node* lC;
    node* rC;
};

void constructBST( node* curNode, int* pre_order, const int size, int* idx );
void printPostOrder( node* curNode );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int* pre_order = new int[10000];
    int size = 0;
    // Input Pre-Order 
    {
        int tmp;
        while ( cin >> tmp )
            pre_order[size++] = tmp;
    }

    node* root = new node{ pre_order[0], 1, 1000000, nullptr, nullptr };
    // Consturct BST
    {   
        int i = 1;
        constructBST( root, pre_order, size, &i );
    }

    // Print Post-order
    printPostOrder( root );

    return 0;
}

void constructBST( node* curNode, int* pre_order, const int size, int* idx )
{
    if ( *idx < size ){
        if ( curNode->l <= pre_order[*idx] && pre_order[*idx] < curNode->val ){
            node* lC = new node{ pre_order[(*idx)++], curNode->l, curNode->val - 1, nullptr, nullptr };
            curNode->lC = lC;
            constructBST( lC, pre_order, size, idx );
        }
    }
    if ( *idx < size ){
        if ( curNode->val < pre_order[*idx] && pre_order[*idx] <= curNode->r ){
            node* rC = new node{ pre_order[(*idx)++], curNode->val + 1, curNode->r, nullptr, nullptr };
            curNode->rC = rC;
            constructBST( rC, pre_order, size, idx );
        }
    }
}
void printPostOrder( node* curNode )
{
    if ( curNode->lC != nullptr )
        printPostOrder( curNode->lC );
    if ( curNode->rC != nullptr )
        printPostOrder( curNode->rC );
    
    cout << curNode->val << "\n";
}