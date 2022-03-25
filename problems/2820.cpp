/* smsh0722
 * 2820
 * 자동차 공장
 * */
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

struct Node{
    int memIdx;
    Node* nextNode;
};
struct child_range{
    int l_child;
    int r_child;
};

int* salary;
int* idxHash; // original to new
int* idxHash_reverse; // new to original
child_range* range_data;
int64_t* ST;
int64_t* lazy;

int rearrange( Node** adjList, int nodeIdx, int newIdx );
int64_t constructSTUtil( int idx, int l, int r );
int64_t updateRangeST( int idx, int l, int r, int trgL, int trgR, int64_t gap );
int64_t getST( int idx, int l, int r, int trg );
void propagation( int idx, int l, int r, int64_t gap );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N; // # of member
    int M; // # of Query
    cin >> N >> M;

    salary = new int[N+1];
    idxHash = new int[N+1];
    idxHash_reverse = new int[N+1];
    range_data = new child_range[N+1];
    {
        Node** adjList = new Node*[N+1];
        for ( int i = 0; i <= N; i++ )
            adjList[i] = nullptr;

        // Input
        cin >> salary[1];
        for ( int i = 2; i <= N; i++ ){
            cin >> salary[i];
            
            int bossIdx;
            cin >> bossIdx;

            Node* newNode = new Node{ i, nullptr };
            newNode->nextNode = adjList[bossIdx];
            adjList[bossIdx] = newNode;
        }

        // Rearrange
        rearrange( adjList, 1, 1 );

        // Delete Original tree
        Node* curNode;
        for ( int i = 0; i <= N; i++ ){
            curNode = adjList[i];
            Node* nextNode;
            while ( curNode != nullptr ){
                Node* nextNode = curNode->nextNode;
                delete curNode;
                curNode = nextNode;
            }
        }
        delete[] adjList;
    }

    // Debug
    /*
    for ( int i = 1; i <= N; i++ ){
        cout << i << ": "
            << idxHash[i] << "["
            << range_data[idxHash[i]].l_child << ", "
            << range_data[idxHash[i]].r_child << "]\n";
    }
    */
   
    // construct ST
    {
        int h = ceil( log2(N) );
        int size = ( 1 << (h + 1) ) - 1;

        ST = new int64_t[size];
        constructSTUtil( 0, 1, N );

        lazy = new int64_t[size];
        memset( lazy, 0, sizeof(int64_t)*size);

    }

    // Ans Query
    char opt;
    for ( int i = 0; i < M; i++ ){
        cin >> opt;
        if ( opt == 'p' ){
            int trg;
            int64_t gap;
            cin >> trg >> gap;
            
            if ( range_data[idxHash[trg]].r_child == 0 )
                continue;
            updateRangeST( 0, 1, N, range_data[idxHash[trg]].l_child, range_data[idxHash[trg]].r_child, gap );
        }
        else { // opt == 'u'
            int trg;
            cin >> trg;
            cout << getST( 0, 1, N, idxHash[trg] ) << "\n";
        }
    }
    return 0;
}

int rearrange( Node** adjList, int nodeIdx, int newIdx )
{
    idxHash[nodeIdx] = newIdx;
    idxHash_reverse[newIdx] = nodeIdx;
    range_data[newIdx].l_child = 0;
    range_data[newIdx].r_child = 0;

    Node* dstNode = adjList[nodeIdx];
    if ( dstNode == nullptr )
        return newIdx;

    range_data[newIdx].l_child = newIdx + 1;
    int r_child = newIdx;
    while ( dstNode != nullptr ){
        r_child = rearrange( adjList, dstNode->memIdx, r_child + 1 );
        dstNode = dstNode->nextNode;
    }
    range_data[newIdx].r_child = r_child;

    return r_child;
}
int64_t constructSTUtil( int idx, int l, int r )
{
    // Base Case
    if ( l == r ){
        int originalIdx = idxHash_reverse[l];
        ST[idx] = salary[originalIdx];
        //cout << "ST: " << ST[idx] << "\n"; // Debug
        return ST[idx];
    }
    
    int mid = ( r - l ) / 2 + l;
    int64_t lval = constructSTUtil( idx*2+1, l, mid );
    int64_t rval = constructSTUtil( idx*2+2, mid + 1, r );
    
    ST[idx] = lval + rval;
    return ST[idx];
}
int64_t updateRangeST( int idx, int l, int r, int trgL, int trgR, int64_t gap )
{
    if ( lazy[idx] != 0 ){
        propagation( idx, l, r, lazy[idx] );
        lazy[idx] = 0;
    }

    // OutOfRange
    if ( trgR < l || r < trgL )
        return ST[idx];
    // In
    if ( trgL <= l && r <= trgR ){
        propagation( idx, l, r, gap );

        return ST[idx];
    }

    // Partly
    int mid = ( r - l ) / 2 + l;
    int64_t lval = updateRangeST( idx*2+1, l, mid, trgL, trgR, gap );
    int64_t rval = updateRangeST( idx*2+2, mid + 1, r, trgL, trgR, gap );

    ST[idx] = lval + rval;
    return ST[idx];
}
int64_t getST( int idx, int l, int r, int trg )
{
    if ( lazy[idx] != 0 ){
        propagation( idx, l, r, lazy[idx] );
        lazy[idx] = 0;
    }

    // OutOfRange
    if ( trg < l || r < trg )
        return 0;
    // In
    if ( l == r && l == trg )
        return ST[idx];
    
    // Partly
    int mid = ( r - l ) / 2 + l;
    int64_t lval = getST( idx*2+1, l, mid, trg );
    int64_t rval = getST( idx*2+2, mid+1, r, trg );

    return (lval + rval);
}
void propagation( int idx, int l, int r, int64_t gap )
{
    ST[idx] += gap;
    if ( l != r ){
        lazy[idx*2+1] += gap;
        lazy[idx*2+2] += gap;
    }
}