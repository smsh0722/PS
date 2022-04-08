/* smsh0722
 * 2517
 * 달리기
 * */
#include <iostream>
#include <cmath>
#include <cstdlib>
#include <cstring>
using namespace std;

struct p_data{
    int rank;
    int level;
};

int comp_level(const void * ap, const void * bp);
int comp_rank(const void * ap, const void * bp);
int getNumOfLower( int* ST, int idx, int l, int r, int re );
int updateST( int* ST, int idx, int l, int r, int trgI, int gap );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N;
    cin >> N;
    
    // Input
    p_data* players = new p_data[N];
    for ( int i = 0; i < N; i++ ){
        cin >> players[i].level;
        players[i].rank = i;
    }

    // Compress level to 0 ~ N-1
    qsort( players, N, sizeof(p_data), comp_level );
    for ( int i = 0; i < N; i++ )
        players[i].level = i;
    // Re-align by rank
    qsort( players, N, sizeof(p_data), comp_rank );

    // Construct ST
    int* ST;
    {
        int h = ceil(log2(N));
        int size = (1<<(h+1)) - 1;
        ST = new int[size];
        memset( ST, 0, sizeof(int)*size );
    }

    // Solve
    for ( int i = 0; i < N; i++ ){
        cout << ( i - getNumOfLower( ST, 0, 0, N - 1, players[i].level ) + 1 ) << "\n";
        updateST( ST, 0, 0, N-1, players[i].level, 1);
    }
    
    return 0;
}

int comp_level(const void * ap, const void * bp)
{
    p_data* a = (p_data*)ap;
    p_data* b = (p_data*)bp;

    return ( a->level - b->level );
}
int comp_rank(const void * ap, const void * bp)
{
    p_data* a = (p_data*)ap;
    p_data* b = (p_data*)bp;

    return ( a->rank - b->rank );
}
int getNumOfLower( int* ST, int idx, int l, int r, int re )
{
    // IN
    if ( r < re )
        return ST[idx];
    // Out
    if ( re <= l )
        return 0;
    // Recursive Find
    int mid = ( r - l ) / 2 + l;
    int lval = getNumOfLower( ST, idx*2+1, l, mid, re );
    int rval = getNumOfLower( ST, idx*2+2, mid+1, r, re );

    return (lval + rval);
}
int updateST( int* ST, int idx, int l, int r, int trgI, int gap )
{
    // IN
    if ( l == r && l == trgI ){
        ST[idx] += gap;
        return ST[idx];
    }
    // OUt
    if ( trgI < l || r < trgI )
        return ST[idx];
    // Recursive
    int mid = ( r - l ) / 2 + l;
    int lval = updateST( ST, idx*2+1, l, mid, trgI, gap );
    int rval = updateST( ST, idx*2+2, mid+1, r, trgI, gap );

    ST[idx] = lval + rval;
    return ST[idx];
}