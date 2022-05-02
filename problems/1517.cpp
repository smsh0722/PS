/* smsh0722
 * 1517
 * 버블 소트
 * */
#include <iostream>
#include <algorithm>
#include <cstring>
#include <cmath>
#include <vector>
using namespace std;

struct seq_data{
    int val;
    int input_idx;
    int sorted_idx;
};

bool compVal( seq_data a, seq_data b );
bool compInput_idx( seq_data a, seq_data b );
int getSumST( int* ST, int idx, int l, int r, int trgL, int trgR );
int updateST( int* ST, int idx, int l, int r, int trgIdx, int gap );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;

    vector<seq_data> A;
    // Construct sequence data
    {
        for ( int i = 0; i < N; i++ ){
            int val;
            cin >> val;
            A.push_back( seq_data{ val, i, -1} );
        }

        sort( A.begin(), A.end(), compVal );
        int sorted_idx = 0;
        A[0].sorted_idx = 0;
        for ( int i = 1; i < N; i++ ){
            sorted_idx += A[i-1].val == A[i].val ? 0 : 1;
            A[i].sorted_idx = sorted_idx;
        }

        sort( A.begin(), A.end(), compInput_idx );
    }

    int* ST;
    // Construct ST
    {
        int h = ceil( log2(N) );
        int size = (1<<(h+1)) - 1;

        ST = new int [size];
        memset( ST, 0, sizeof(int)*size );
    }

    /* answer
     * max == N^2 (N = 500,000)
     * int64_t
     * */
    int64_t swap_count = 0;
    // Solve
    for ( int i = N - 1; i >= 0; i-- ){
        swap_count += (int64_t)getSumST( ST, 0, 0, N-1, 0, A[i].sorted_idx - 1 );
        updateST( ST, 0, 0, N-1, A[i].sorted_idx, 1 );
    }

    cout << swap_count;

    return 0;
}

bool compVal( seq_data a, seq_data b )
{
    return ( a.val < b.val );
}
bool compInput_idx( seq_data a, seq_data b )
{
    return ( a.input_idx < b.input_idx );
}
int getSumST( int* ST, int idx, int l, int r, int trgL, int trgR )
{
    // In range
    if ( trgL <= l && r <= trgR)
        return ST[idx];
    // OutOfRange
    if ( trgR < l || r < trgL )
        return 0;
    // Partly In
    int mid = (r-l)/2 + l;
    int lval = getSumST( ST, idx*2+1, l, mid, trgL, trgR );
    int rval = getSumST( ST, idx*2+2, mid+1, r, trgL, trgR );

    return (lval+rval);
}
int updateST( int* ST, int idx, int l, int r, int trgIdx, int gap )
{
    if ( l == r && trgIdx == l){
        ST[idx] += gap;
        return ST[idx];
    }
    // OutOfRange
    if ( trgIdx < l || r < trgIdx )
        return ST[idx];
    // In range
    int mid = (r - l ) / 2 + l;
    int lval = updateST( ST, idx*2+1, l, mid, trgIdx, gap );
    int rval = updateST( ST, idx*2+2, mid+1, r, trgIdx, gap );

    ST[idx] = lval + rval;
    return ST[idx];
}