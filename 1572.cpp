/* smsh0722
 * 1572
 * 중앙값
 * */
#include <iostream>
#include <cmath>
#include <cstring>
#include <queue>
using namespace std;

const int MAX_IN = 66536;

int updateST( int* ST, int idx, int l, int r, int trgIdx, int gap ); 
int getMedianST( int* ST, int idx, int l, int r, int curRank, int trgRank );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N, K;
    cin >> N >> K;

    int* ST;
    {
        int h = ceil( log2(MAX_IN + 1 ) );
        int size = (2<<(h+1))-1;
        ST = new int[size];
        memset( ST, 0, sizeof(int)*size );
    }

    queue<int> old_data;
    for ( int i = 0; i < K; i++ ){
        int val;
        cin >> val;
        updateST( ST, 0, 0, MAX_IN, val, 1 );        
        old_data.push(val);
    }

    int64_t sum = 0;
    // Solve
    {
        const int median_rank = (K+1)/2;
        int val;

        // Cal sum
        sum += int64_t( getMedianST( ST, 0, 0, MAX_IN, 0, median_rank ) );
        for ( int i = 0; i < N - K; i++ ){
            // Pop Data
            updateST( ST, 0, 0, MAX_IN, old_data.front(), -1 );
            old_data.pop();

            // Push Data
            cin >> val;
            updateST( ST, 0, 0, MAX_IN, val, 1 );
            old_data.push(val);

            // Cal sum
            sum += int64_t( getMedianST( ST, 0, 0, MAX_IN, 0, median_rank ) );
        }
    }

    // Print Result
    cout << sum;
    return 0;
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

    ST[idx] = (lval + rval);

    return ST[idx];
}
int getMedianST( int* ST, int idx, int l, int r, int curRank, int trgRank )
{
    if ( l == r )
        return l;
    
    int lval = ST[idx*2+1];
    int rval = ST[idx*2+2];
    int mid = ( r - l )/ 2 + l;
    if ( (curRank + lval) >= trgRank )
        return getMedianST( ST, idx*2+1, l, mid, curRank, trgRank );
    else 
        return getMedianST( ST, idx*2+2, mid+1, r, curRank + lval, trgRank );
}