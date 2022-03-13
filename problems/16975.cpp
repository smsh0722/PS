/* smsh0722
 * 16975
 * 수열과 쿼리 21
 * Lazy Segment Tree
 * */
#include <iostream>
#include <cmath>
using namespace std;

const int MAXSTSIZE = 262143; // 2^18 - 1;

int64_t* lazy;
int64_t* ST;

int64_t* constructST( int* numArr, int N );
int64_t constructSTUtil( int64_t* ST, int* numArr, int idx, int l, int r );
int64_t updateRangeST( int idx, int l, int r, int trgL, int trgR, int64_t diff );
void propagation( int idx, int l, int r, int64_t diff );
int64_t getVal( int idx, int l, int r, int trgI );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;

    // Construct ST
    {
        int* numArr = new int[N];
        for ( int i = 0; i < N; i++ )
            cin >> numArr[i];
        
        ST = constructST( numArr, N );

        delete[] numArr; 
    }

    // Construct Lazy
    {
        lazy = new int64_t[MAXSTSIZE];

        for ( int i = 0; i < MAXSTSIZE; i++ )
            lazy[i] = 0;
    }

    // Query
    int M; // # of Query
    cin >> M;
    for ( int i = 0; i < M; i++ ){
        int query;
        cin >> query;

        if ( query == 1 ){
            int i, j, k;
            cin >> i >> j >> k;
            updateRangeST( 0, 0, N-1, i-1, j-1, k ); // Add k to range i-1 ~ j-1
        }
        else {
            int x;
            cin >> x;
            cout << getVal( 0, 0, N-1, x-1 ) << "\n"; // Get Val x-1
        }
    }

    return 0;
}
int64_t* constructST( int* numArr, int N )
{
    // int h = ceil( log2(N) );
    // int size = (int)pow( 2, h + 1 ) - 1;

    int64_t* ST = new int64_t[MAXSTSIZE];
    constructSTUtil( ST, numArr, 0, 0, N-1 );
    
    return ST;
}
int64_t constructSTUtil( int64_t* ST, int* numArr, int idx, int l, int r )
{
    // Base case
    if ( l == r ){
        ST[idx] = (int64_t)numArr[l];
        return ST[idx];
    }

    int mid = ( r - l ) / 2 + l;
    int64_t lval = constructSTUtil( ST, numArr, idx*2+1, l, mid );
    int64_t rval = constructSTUtil( ST, numArr, idx*2+2, mid + 1, r );

    ST[idx] = lval + rval;

    return ST[idx];
}
int64_t updateRangeST( int idx, int l, int r, int trgL, int trgR, int64_t diff )
{
    // If Pending
    if ( lazy[idx] != 0 )
       propagation( idx, l, r, lazy[idx] );
    
    // OutOfRange
    if ( trgR < l || r < trgL )
        return ST[idx];
    // In
    if ( trgL <= l && r <= trgR ){
        propagation( idx, l, r, diff );
        return ST[idx];
    }
    // Partly In
    int mid = ( r - l ) / 2 + l;
    int64_t lval = updateRangeST( idx*2+1, l, mid, trgL, trgR, diff );
    int64_t rval = updateRangeST( idx*2+2, mid+1, r, trgL, trgR, diff );

    ST[idx] = lval + rval;
    return ST[idx];
}
void propagation( int idx, int l, int r, int64_t diff )
{
    ST[idx] += diff * ( r - l + 1 );
    if ( l < r ){ // Postpone updating children
        lazy[idx*2+1] += diff;
        lazy[idx*2+2] += diff;
    }
    lazy[idx] = 0;
}
int64_t getVal( int idx, int l, int r, int trgI )
{
    // If pending
    if ( lazy[idx] != 0 )
        propagation( idx, l, r, lazy[idx] );
    // OutOfRange
    if ( trgI < l || r < trgI )
        return 0;
    // Base Case
    if ( l == r && l == trgI )
        return ST[idx];

    // Recursive Call
    int mid = ( r - l ) / 2 + l;
    int64_t lval = getVal( idx*2+1, l, mid, trgI );
    int64_t rval = getVal( idx*2+2, mid+1, r, trgI );

    return lval + rval;
}