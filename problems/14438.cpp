#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int INF = INT32_MAX;

struct SegTree{
    int h;
    int size;
    vector<int> arr;
};

SegTree st;

// # of elements
int N;
// # of Queries
int M;

vector<int> elements;

int BuildST( int node, int l, int r )
{
    if ( l == r )
        return st.arr[node] = elements[l];

    int mid = (r-l)/2+l;
    return (st.arr[node] = min(BuildST(node*2+1, l, mid ), BuildST(node*2+2, mid+1, r)));
}

int UpdateST( int node, int l, int r, int trg, int val )
{
    if ( trg < l || r < trg )
        return st.arr[node];
    if ( l == r && l == trg )
        return st.arr[node] = val;
    
    int mid = (r-l)/2+l;
    return (st.arr[node] = min( UpdateST(node*2+1, l, mid, trg, val ), UpdateST(node*2+2, mid+1, r, trg, val) ) );
}

int GetMinST( int node, int l, int r, int tl, int tr )
{
    if ( tr < l || r < tl )
        return INF;
    if ( tl <= l && r <= tr )
        return st.arr[node];
    
    int mid = (r-l)/2+l;
    return min( GetMinST(node*2+1, l, mid, tl, tr), GetMinST(node*2+2, mid+1, r, tl, tr ) );
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    elements.resize(N+1, INF);
    for ( int i = 1; i <= N; i++ )
        cin >> elements[i];
    
    // Build SegTree
    st.h = ceil(log2(N+1));
    st.size = (1<<(st.h+1))-1;
    st.arr.resize(st.size, INF);
    BuildST(0, 0, N);

    // Anser queries
    cin >> M;
    for ( int mi = 0; mi < M; mi++ ){
        int opt, i, j;
        cin >> opt >> i >> j;
        if ( opt == 1 ){ // Change elements[i] = v
            UpdateST(0, 0, N, i, j );
        }
        else {// opt == 2 Get Min in [i,j]
            cout << GetMinST(0, 0, N, i, j ) << "\n";
        }
    }

    return 0;
}