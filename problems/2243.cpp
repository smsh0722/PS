/* smsh0722
 * 2243
 * 사탕상자
 * */
#include <iostream>
#include <cmath>
#include <cstring>

using namespace std;

int getCandyNumST( int* ST, int idx, int l, int r, int count, int trgRank );
int updateST( int* ST, int idx, int l, int r, int candyNum, int quantity );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n;
    cin >> n;

    int* ST;
    {
        int h = ceil( log2(1000001) ); // 1~1,000,000
        int size = (1<<(h+1)) - 1;
        ST = new int[size];
        memset( ST, 0, sizeof(int)*size );
    }

    for ( int actIdx = 1; actIdx <= n; actIdx++ ){
        int opt;
        cin >> opt;
        if ( opt == 1 ) { // Pop
            int rank;
            cin >> rank;

            int candyNum = getCandyNumST( ST, 0, 1, 1000000, 0, rank );
            updateST( ST, 0, 1, 1000000, candyNum, -1 );
            cout << candyNum << "\n";

        }
        else { // (opt == 2) Push
            int candyNum, quantity;
            cin >> candyNum >> quantity;
            updateST( ST, 0, 1, 1000000, candyNum, quantity );
        }
    }
}
int getCandyNumST( int* ST, int idx, int l, int r, int count, int trgRank )
{
    // Base Case
    if ( l == r && (ST[idx] + count >= trgRank) )
        return l;

    // Recursive Find
    int mid = ( r - l ) / 2 + l;
    int lval = ST[idx*2+1];
    if ( count + lval >= trgRank ) // left Case
        return getCandyNumST( ST, idx*2+1, l, mid, count, trgRank );
    // ( count + lval < trgRank ) Right Case
    return getCandyNumST( ST, idx*2+2, mid+1, r, count + lval, trgRank );
}
int updateST( int* ST, int idx, int l, int r, int candyNum, int quantity )
{
    // Base Case 
    if ( l == r && l == candyNum ){
        ST[idx] += quantity;
        return ST[idx];
    }
    // OutOfRange
    if ( candyNum < l || r < candyNum )
        return ST[idx];

    // Recursive update
    int mid = ( r - l ) / 2 + l;
    int lval = updateST( ST, idx*2+1, l, mid, candyNum, quantity );
    int rval = updateST( ST, idx*2+2, mid+1, r, candyNum, quantity );

    ST[idx] = lval + rval;

    return ST[idx];
}