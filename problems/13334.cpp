/* NOTE:
segment Tree 풀이.
sweeping으로 더 짧게 풀 수 있다.

*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Position{
    int l, r;
};

struct SegTree{
    int h;
    int size;
    vector<int> arr;
};

const int MAX_N = 100000;
const int MAX_POS_LENGTH = MAX_N*2;
const int MAX_POS = 100000000;

int n; // num of people
int d; // length of train

vector<Position> vec;
vector<int> compressedPos;
SegTree st;

bool PositionLDesc( const Position& a, const Position& b )
{
    if ( a.l == b.l )
        return a.r < b.r;
    return a.l > b.l;
};

int AddST( int node, int l, int r, int trg, int val )
{
    if ( l == r && l == trg )
        return (st.arr[node] += val);
    if ( trg < l || r < trg )
        return st.arr[node];
    
    int mid = (r-l)/ 2 + l;
    return ( st.arr[node] = 
                AddST(node*2+1, l, mid, trg, val ) +
                AddST(node*2+2, mid+1, r, trg, val ) );
}
int GetSumST( int node, int l, int r, int tl, int tr )
{
    if ( tl <= l && r <= tr )
        return st.arr[node];
    if ( r < tl || tr < l )
        return 0;
    
    int mid = (r-l)/2 + l;
    return ( GetSumST(node*2+1, l, mid, tl, tr) + GetSumST(node*2+2, mid+1, r, tl, tr ) );
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    for ( int i = 0; i < n; i++ ){
        int l, r;
        cin >> l >> r;
        if ( l > r ){
            int tmp = r;
            r = l;
            l = tmp;
        }
        vec.push_back({l, r }); 
        compressedPos.push_back(l);
        compressedPos.push_back(r);
    }
    cin >> d;

    sort( compressedPos.begin(), compressedPos.end());
    compressedPos.erase( unique(compressedPos.begin(), compressedPos.end() ), compressedPos.end() );

    sort( vec.begin(), vec.end(), PositionLDesc);

    st.h = ceil(log2(MAX_POS_LENGTH));
    st.size = (1<<(st.h+1)) - 1;
    st.arr.resize( st.size, 0 );
    
    for ( size_t i = 0; i < compressedPos.size(); i++ ){ // Debug
        printf("[%d]: %d ", i , compressedPos[i]);
    } cout << endl;

    int ans = 0;
    for ( int i = 0; i < n; i++ ){
        Position p = vec[i];
        int ri = lower_bound(compressedPos.begin(), compressedPos.end(), p.r ) - compressedPos.begin();
        AddST(0, 0, MAX_POS_LENGTH-1, ri, 1 );
        int tl = lower_bound(compressedPos.begin(), compressedPos.end(), p.l ) - compressedPos.begin();
        int tr = (int)min( int64_t(MAX_POS), int64_t(p.l)+d );
        tr = upper_bound(compressedPos.begin(), compressedPos.end(), tr ) - compressedPos.begin();
        tr--;
        printf( "p(%d, %d), ti(%d, %d)\n", p.l, p.r, tl, tr );//Debug
        if ( tr >= 0 ){
            int tmpSum = GetSumST(0, 0, MAX_POS_LENGTH-1, tl, tr );
            cout << "tmpSum: " << tmpSum << endl;// Debug
            ans = ans < tmpSum ? tmpSum : ans;
        }
    }

    cout << ans;

    return 0;
}