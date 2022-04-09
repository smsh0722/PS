/* smsh0722
 * 2336
 * 굉장한 학생
 * */
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int N;
int MAX_RANK = 500001;

struct st_node{
    bool exist;
    int rankB_highest;
};
struct ranking{
    int A;
    int B;
};

void constructSTUtil( st_node* ST, int idx, int l, int r, int* rankA2Idx, ranking* idx2Rank );
bool isInferior( st_node* ST, int idx, int l, int r, ranking trgRank );
st_node updateST( st_node* ST, int idx, int l, int r, ranking trgRank );
void printST( st_node* ST, int idx = 0, int l = 1, int r = N );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;

    // Hash stuIdx to rankA or rankB
    ranking* idx2Rank = new ranking[N+1];
    int* rankA2Idx = new int[N+1];
    {
        int stuIdx;
        for ( int i = 1; i <= N; i++ ){
            cin >> stuIdx;
            idx2Rank[stuIdx].A = i;
            rankA2Idx[i] = stuIdx;
        }
        for ( int i = 1; i <= N; i++ ){
            cin >> stuIdx;
            idx2Rank[stuIdx].B = i;
        }
    }

    st_node* ST;
    {
        int h = ceil( log2(N) );
        int size = (1<<(h+1)) - 1;
        ST = new st_node[size];
        constructSTUtil( ST, 0, 1, N, rankA2Idx, idx2Rank );
    }
    // cout << "\n"; printST( ST ); // Debug

    int count = N;
    {
        int stuIdx;
        for ( int i = 0; i < N; i++ ){
            cin >> stuIdx;
            count -= isInferior( ST, 0, 1, N, idx2Rank[stuIdx] );

            updateST( ST, 0, 1, N, idx2Rank[stuIdx] );
            // cout << "\n"; printST( ST ); // Debug
        }
    }

    cout << count;

    return 0;
}
void constructSTUtil( st_node* ST, int idx, int l, int r, int* rankA2Idx, ranking* idx2Rank )
{
    // Base Case
    if ( l == r ){
        ST[idx].exist = false;
        int stuIdx = rankA2Idx[l];
        ST[idx].rankB_highest = idx2Rank[stuIdx].B;
        return;
    }

    // Recursive
    int mid = (r - l ) / 2 + l;
    constructSTUtil( ST, idx*2+1, l, mid, rankA2Idx, idx2Rank );
    constructSTUtil( ST, idx*2+2, mid+1, r, rankA2Idx, idx2Rank );

    ST[idx].exist = false;
    ST[idx].rankB_highest = MAX_RANK;
}
bool isInferior( st_node* ST, int idx, int l, int r, ranking trgRank )
{
    // OutOfRange
    if ( trgRank.A <= l || r < 1 )
        return false;
    // In range
    if ( trgRank.A > r ){
        if ( ST[idx].exist == false )
            return false;
        // Exist
        return (ST[idx].rankB_highest < trgRank.B);
    }

    // Partly In
    int mid = (r - l ) / 2 + l;
    bool lval = isInferior( ST, idx*2+1, l, mid, trgRank );
    bool rval = isInferior( ST, idx*2+2, mid+1, r, trgRank );
    return (lval|rval);
}
st_node updateST( st_node* ST, int idx, int l, int r, ranking trgRank )
{
    // Trg
    if ( l == r && l == trgRank.A ){
        ST[idx].exist = true;
        return ST[idx];
    }
    // OutOfRange
    if ( trgRank.A < l || r < trgRank.A )
        return ST[idx];
    
    // Recursive
    int mid = ( r - l ) / 2 + l;
    st_node lval = updateST( ST, idx*2+1, l, mid, trgRank );
    st_node rval = updateST( ST, idx*2+2, mid+1, r, trgRank );
    lval.rankB_highest = lval.exist == false ? MAX_RANK : lval.rankB_highest;
    rval.rankB_highest = rval.exist == false ? MAX_RANK : rval.rankB_highest;

    ST[idx] = lval.rankB_highest < rval.rankB_highest ? lval : rval;
    return ST[idx];
}
void printST( st_node* ST, int idx, int l, int r )
{
    cout << l << ", " << r << " : "
        << ST[idx].exist << " "
        << ST[idx].rankB_highest << "\n";
    if( l != r ){
        int mid = ( r-l)/2 + l;
        printST( ST, idx*2+1, l, mid );
        printST( ST, idx*2+2, mid+1, r );
    }
}