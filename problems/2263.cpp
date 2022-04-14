/* smsh0722
 * 2263
 * 트리의 순회
 * */
#include <iostream>
using namespace std;

struct tree_node{
    int nodeNum;
    tree_node* l_child;
    tree_node* r_child;
};

int* inOrder;
int* nodeIdx_in;
int* postOrder;

void solve( tree_node* curNode, int* idx, int l, int r );
void DFS_preOrder( tree_node* curNode );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    tree_node* root = nullptr;
    int n;
    
    // Input
    cin >> n;
    inOrder = new int[n];
    nodeIdx_in = new int[n+1];
    for ( int i = 0; i < n; i++ ){
        cin >> inOrder[i];
        nodeIdx_in[ inOrder[i] ] = i;
    }
    postOrder = new int[n];
    for ( int i = 0; i < n; i++ )
        cin >> postOrder[i];
    
    // Solve
    {
        root = new tree_node;
        int idx = n-1;
        solve( root, &idx, 0, n-1 );
    }
    // DFS-pre
    DFS_preOrder( root );

    return 0;
}
void solve( tree_node* curNode, int* idx, int l, int r )
{
    curNode->nodeNum = postOrder[*idx];
    curNode->l_child = nullptr;
    curNode->r_child = nullptr;
    // End
    if ( l == r )
        return;
    
    // Recursively Find
    int mid = nodeIdx_in[postOrder[*idx]];
    if ( *idx > 0 && ((mid+1)<= r)){
        tree_node* r_child = new tree_node;
        curNode->r_child = r_child;
        
        (*idx)--;
        solve( r_child, idx, mid+1, r );
    }
    if ( *idx > 0 && (l<=(mid-1)) ){
        tree_node* l_child = new tree_node;
        curNode->l_child = l_child;

        (*idx)--;
        solve( l_child, idx, l, mid-1 );
    }
}
void DFS_preOrder( tree_node* curNode )
{   
    cout << curNode->nodeNum << " ";
    // DFS
    if( curNode->l_child != nullptr )
        DFS_preOrder( curNode->l_child );
    if ( curNode->r_child != nullptr )
        DFS_preOrder( curNode->r_child );
}