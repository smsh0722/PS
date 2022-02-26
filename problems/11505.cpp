/* smsh0722
 * 11505
 * 구간 곱 구하기
 * */
#include <iostream>
#include <cmath>
using namespace std;

const int ENDNUM = 1000000007; // 1,000,000,007

int* constructST( int numArr[], const int n );
int constructSTUtil( int ST[], int numArr[], int idx, int l, int r );
int updateST( int ST[], int idx, int l, int r, int trgIdx, int val );
int queryST( int ST[], int idx, int l, int r, int trgL, int trgR );

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    int N; // # of number
    int M; // # of update
    int K; // # of query
    int* numArr = new int[1000000];

    cin >> N >> M >> K;
    
    for ( int i = 0; i < N; i++ )
        cin >> numArr[i];
    
    int* ST = constructST( numArr, N );


    int a, b, c;
    while ( M + K > 0 ){
        cin >> a >> b >> c;
        if ( a == 1 ){ // Update numArr[b-1] to c
            --M;
            updateST( ST, 0, 0, N-1, b-1, c );
        }
        else { // a == 2, Query from b-1 to c-1
            --K;
            cout << queryST( ST, 0, 0, N-1, b-1, c-1 ) << "\n";
        }
    }
}

int* constructST( int numArr[], const int n )
{
    int h = ceil( log2(n) );
    int size = pow( 2, h + 1 ) - 1;

    int* ST = new int[size];

    constructSTUtil( ST, numArr, 0, 0, n-1 );
    return ST;
}
int constructSTUtil( int ST[], int numArr[], int idx, int l, int r )
{
    // Base Case
    if ( l == r ){
        ST[idx] = numArr[l];
        return ST[idx];
    }
    
    // Calculate Recursively
    int mid = ( r - l ) / 2 + l;
    int lval = constructSTUtil( ST, numArr, idx * 2 + 1, l, mid );
    int rval = constructSTUtil( ST, numArr, idx * 2 + 2, mid + 1, r );

    ST[idx] = ( (int64_t)lval * rval) % ENDNUM;
    return ST[idx];
}
int updateST( int ST[], int idx, int l, int r, int trgIdx, int val )
{
    // OutOfRange
    if ( trgIdx < l || r < trgIdx )
        return ST[idx];

    // Base Case
    if ( l == r && l == trgIdx ){
        ST[idx] = val;
        return val;
    }
    
    // Range
    int mid = ( r - l ) / 2 + l;
    int lval = updateST( ST, idx * 2 + 1, l, mid, trgIdx, val );
    int rval = updateST( ST, idx * 2 + 2, mid + 1, r, trgIdx, val );
    
    ST[idx] = ( (int64_t)lval * rval ) % ENDNUM;
    return ST[idx];
}
int queryST( int ST[], int idx, int l, int r, int trgL, int trgR )
{
    // Out of Range
    if ( trgR < l || r < trgL )
        return 1;

    // In
    if ( trgL <= l && r <= trgR )
        return ST[idx];
    
    // Partly In
    int mid = ( r - l ) / 2 + l;
    int lval = queryST( ST, idx * 2 + 1, l, mid, trgL, trgR );
    int rval = queryST( ST, idx * 2 + 2, mid + 1, r, trgL, trgR );
    return ( ( (int64_t)lval * rval ) % ENDNUM );
}