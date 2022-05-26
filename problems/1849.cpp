/* smsh0722
 * 1849
 * 순열
 * */
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int N;

int* constructST();
int constructSTUtil( int* ST, int idx, int l, int r );
int getIdxST( int* ST, int idx, int l, int r, int curCount, int trgCount );
int updateST( int* ST, int idx, int l, int r, int trgIdx, int gap );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;    

    int* seq;
    {
        seq = new int[N+1];
        memset( seq, 0, sizeof(int)*(N+1) );
    }

    // Solve
    {
        int* A;
        {
            A = new int[N+1];
            for ( int i = 1; i <= N; i++ )
                cin >> A[i];    
        }

        int* ST;
        ST = constructST( );

        for ( int i = 1; i <= N; i++ ){
            int idx = getIdxST( ST, 0, 1, N, 0, A[i] );
            seq[idx] = i;
            updateST( ST, 0, 1, N, idx, -1 );
        }

        delete[] A;
        delete[] ST;
    }

    // Print answer
    for ( int i = 1; i <= N; i++ )
        cout << seq[i] << "\n";
    
    return 0;
}

int* constructST()
{
    int* ST;
    int h = ceil( log2(N+1) );
    int size = (1<<(h+1))-1;
    ST = new int [size];

    constructSTUtil( ST, 0, 1, N );

    return ST;
}
int constructSTUtil( int* ST, int idx, int l, int r )
{
    if ( l == r ){
        ST[idx] = 1;
        return ST[idx];
    }

    int mid = (r-l)/2 + l;
    int lval = constructSTUtil( ST, idx*2+1, l, mid );
    int rval = constructSTUtil( ST, idx*2+2, mid+1, r );

    ST[idx] = lval + rval;

    return ST[idx];
}
int getIdxST( int* ST, int idx, int l, int r, int curCount, int trgCount )
{
    if ( l == r )
        return l;
    
    int mid = (r-l)/2 +l;
    if ( curCount + ST[idx*2+1] > trgCount )
        return getIdxST( ST, idx*2+1, l, mid, curCount, trgCount );
    else 
        return getIdxST(ST, idx*2+2, mid+1, r, curCount+ST[idx*2+1], trgCount );
}
int updateST( int* ST, int idx, int l, int r, int trgIdx, int gap )
{
    if ( l == r && l == trgIdx ){
        ST[idx] += gap;
        return ST[idx];
    }
    if ( trgIdx < l || r < trgIdx )
        return ST[idx];
    
    int mid = ( r - l ) / 2 + l;
    int lval = updateST( ST, idx*2+1, l, mid, trgIdx, gap );
    int rval = updateST( ST, idx*2+2, mid+1, r, trgIdx, gap );

    ST[idx] = lval + rval;

    return ST[idx];
}