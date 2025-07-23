#include <iostream>
#include <vector>

using namespace std;

struct Node{
    int sum;
    int lw;
    int lu;
    int rw;
    int ru;
};

int k; // height of tree
int tSize; // size of tree
vector<Node> Tree;

int SumDFS( int node, int prefSum, int l, int r )
{
    Tree[node].sum = prefSum;    
    if ( l== r){
        return prefSum;
    }

    int mid = (r-l)/2+l;
    int lRst = SumDFS(node*2+1, prefSum+Tree[node].lw, l, mid );
    int rRst = SumDFS(node*2+2, prefSum+Tree[node].rw, mid+1, r);

    return max(lRst, rRst);
}

int PrepareUpdateDFS( int node, int max, int l, int r )
{
    if ( l == r ){
        return max - Tree[node].sum;
    }

    int mid = (r-l)/2+l;
    int lRst = PrepareUpdateDFS(node*2+1, max, l, mid);
    int rRst = PrepareUpdateDFS(node*2+2, max, mid+1, r );

    Tree[node].lu = lRst;
    Tree[node].ru = rRst;

    return min(lRst, rRst);
}

int64_t UpdateDFS( int node, int prefUpdate, int l, int r )
{
    if ( l == r ){
        return 0;
    }

    Tree[node].lw += Tree[node].lu - prefUpdate;
    Tree[node].rw += Tree[node].ru - prefUpdate;

    int mid = (r-l)/2+l;
    int64_t lRst = UpdateDFS(node*2+1, Tree[node].lu, l, mid );
    int64_t rRst = UpdateDFS(node*2+2, Tree[node].ru, mid+1, r);
    
    return (lRst+rRst+Tree[node].lw+Tree[node].rw);
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> k;
    tSize = (1<<(k+1))-1;
    Tree.resize(tSize, {0,0,0,0,0});

    for ( int i = 0; i < (1<<k)-1; i++ ){
        int lw, rw;
        cin >> lw >> rw;
        Tree[i].lw = lw;
        Tree[i].rw = rw;
    }

    int max = SumDFS(0, 0, 0, (1<<k));
    
    PrepareUpdateDFS(0,max, 0, (1<<k));
    
    cout << UpdateDFS(0, 0, 0, (1<<k));

    return 0;
}