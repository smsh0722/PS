/* smsh0722
 * 9426
 * 중앙값 측정
 * */
#include <iostream>
#include <cstring>
#include <queue>
#include <cmath>
using namespace std;

int constructSTUtil( int* ST, int idx, int l, int r, int* vals );
int getMedianST( int* ST, int idx, int l, int r, int count, int medianCount );
int updateST( int* ST, int idx, int l, int r, int trg, int gap );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, K;
    cin >> N >> K;

    // Ans
    int64_t sum = 0;
    {
        int medianCount = ( K + 1 ) / 2;

        // cur Val
        int curVal;
        queue<int> Q;

        int* vals = new int[65536];// 0 ~ 65536;
        memset( vals, 0, sizeof(int)*65536 );
        
        // first k 
        for ( int i = 0; i < K; i++ ){
            cin >> curVal;
            Q.push(curVal);

            vals[curVal]++;
        }
        
        // Construtc ST 
        int* ST;
        {
            int h = ceil( log2(65536) );
            int size = (1 << (h+1)) - 1;
            ST = new int[size];
            constructSTUtil( ST, 0, 0, 65535, vals );
        }

        // Get 1st Median
        sum += getMedianST( ST, 0, 0, 65535, 0, medianCount );

        // Get 2nd ~ (N-K+1)th Median
        for ( int i = 0; i < N - K; i++ ){
            cin >> curVal;
            Q.push( curVal );

            updateST( ST, 0, 0, 65535, Q.front(), -1 ); Q.pop(); // pop oldVal

            updateST( ST, 0, 0, 65535, curVal, 1 ); // push newVal

            sum += getMedianST( ST, 0, 0, 65535, 0, medianCount );
        }
    }

    // return rst
    cout << sum;
    return 0;
}

int constructSTUtil( int* ST, int idx, int l, int r, int* vals )
{
    // Base Case
    if ( l == r ){
        ST[idx] = vals[l];
        return ST[idx];
    }
    
    int mid = ( r - l ) / 2 + l;
    int lval = constructSTUtil( ST, idx * 2 + 1, l, mid, vals );
    int rval = constructSTUtil( ST, idx * 2 + 2, mid + 1, r, vals );
    ST[idx] = lval + rval;

    return ST[idx];
}
int getMedianST( int* ST, int idx, int l, int r, int count, int medianCount )
{
    // Ans
    if( l == r && ( medianCount <= (count + ST[idx]) ) )
        return l;

    // Recursive Find
    int mid = ( r - l ) / 2 + l;
    int lval = ST[idx*2+1];
    // Case Left
    if ( count + lval >= medianCount )
        return getMedianST( ST, idx*2+1, l, mid, count, medianCount );
    // Case Right
    return getMedianST( ST, idx*2+2, mid + 1, r, count + lval, medianCount );    
}
int updateST( int* ST, int idx, int l, int r, int trg, int gap )
{
    // Base Case
    if ( l == r && l == trg ){
        ST[idx] += gap;
        return ST[idx];
    }
    // OutOfRange
    if( trg < l || r < trg )
        return ST[idx];
    
    // In
    int mid = ( r - l ) / 2 + l;
    int lval = updateST( ST, idx*2+1, l, mid, trg, gap);
    int rval = updateST( ST, idx*2+2, mid+1, r, trg, gap );

    ST[idx] = lval + rval;
    return ST[idx];
}