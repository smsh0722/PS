/* smsh0722
 * 3653
 * 영화 수집
 * */
#include <iostream>
#include <cmath>
using namespace std;

void solution();
int* constructST( int n, int m );
void constructSTUtil( int ST[], int idx, int l, int r, int m );
int getNumOfAbove( int ST[], int idx, int l, int r, int trgIdx );
void updateST( int ST[], int idx, int l, int r, int trgPos, int gap );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int tNum; cin >> tNum;

    for ( int i = 0; i < tNum; i++ )
        solution();
    return 0;
}

void solution()
{
    int n, m;
    cin >> n >> m;

    int* movies = new int[n];
    for ( int i = 0; i < n; i++ )
        movies[i] = m + i;

    int* ST = constructST( n, m ); // lEnd = 0, rEnd = n + m - 1;

    for ( int i = 0; i < m; i++ ){
        int movieIdx; cin >> movieIdx;
        movieIdx--;
        int prevPos = movies[movieIdx];
        int newPos = ( m - i ) - 1;

        cout << getNumOfAbove( ST, 0, 0, n + m - 1, prevPos-1 ) << " ";

        updateST( ST, 0, 0, n + m - 1, prevPos, -1 ); // pop
        updateST( ST, 0, 0, n + m - 1, newPos, +1 ); // push
        movies[movieIdx] = newPos;
    }
    cout << "\n";
}
int* constructST( int n, int m )
{
    int height = ceil( log2(n+m) );
    int size = pow( 2, height+1 ) - 1;

    int* ST = new int[size];
    constructSTUtil( ST, 0, 0, n + m - 1, m );

    return ST;
}
void constructSTUtil( int ST[], int idx, int l, int r, int m )
{
    // Base Case
    if ( l == r ){
        if ( r < m ) // 0 ~ ( m - 1 )
            ST[idx] = 0;
        else // m ~ 
            ST[idx] = 1;
        
        return;
    }

    int mid = ( r - l ) / 2 + l;
    constructSTUtil( ST, idx * 2 + 1, l, mid, m );
    constructSTUtil( ST, idx * 2 + 2, mid + 1, r, m );

    ST[idx] = ST[idx*2+1] + ST[idx*2+2];
}
int getNumOfAbove( int ST[], int idx, int l, int r, int trgIdx )
{
    // OutOfRange
    if ( trgIdx < l || r < 0 )
        return 0;
    
    // In range
    if ( 0 <= l && r <= trgIdx )
        return ST[idx];
    
    // Partly In
    int mid = ( r - l ) / 2 + l;
    int lval = getNumOfAbove( ST, idx*2+1, l, mid, trgIdx );
    int rval = getNumOfAbove( ST, idx*2+2, mid + 1, r, trgIdx );

    return lval + rval;
}
void updateST( int ST[], int idx, int l, int r, int trgPos, int gap )
{
    // OutOfRange
    if ( trgPos < l || r < trgPos )
        return;
    
    ST[idx] += gap;

    if ( l < r ){
        int mid = ( r - l ) / 2 + l;
        updateST( ST, idx*2+1, l, mid, trgPos, gap );
        updateST( ST, idx*2+2, mid+1, r, trgPos, gap );
    }
}