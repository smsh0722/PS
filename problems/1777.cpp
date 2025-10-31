#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct SegTree{
    int N;
    int h;
    int size;
    vector<int> arr;
};

int N;

vector<int> inverseSeq;
vector<int> ans;

SegTree st;

int ConstructST( int node, int l, int r )
{
    if ( l == r )
        return st.arr[node] = 1;
    
    int mid = (r-l)/2 + l;
    return st.arr[node] = ConstructST( node*2+1, l, mid )
                            + ConstructST( node*2+2, mid+1, r );
}
int AddST( int node, int l, int r, int trg, int val )
{
    if ( trg < l || r < trg )
        return st.arr[node];
    if ( l == r )
        return st.arr[node] += val;
    
    int mid = (r-l)/2 +l;
    return (st.arr[node] = AddST(node*2+1, l, mid, trg, val ) + AddST(node*2+2, mid+1, r, trg, val ) );
}

int GetIdxST( int node, int l, int r, int& trgCount )
{
    // printf( "st: %d, l: %d, r: %d, trgCount: %d\n", st.arr[node], l, r, trgCount ); // DEBUG
    if ( st.arr[node] == trgCount && ans[l] == 0 ){
        trgCount = 0;
        return l;
    }
    else if ( st.arr[node] < trgCount ){
        trgCount -= st.arr[node];
        return l;
    }

    // st.arr[node] > trgCount

    int mid = (r-l)/2 + l;
    int idx = GetIdxST( node*2+2, mid+1, r, trgCount );
    if ( trgCount == 0 ){
        return idx;
    }
    // trgCount > 0 || trgCount == 0 && ans[idx] != 0
    return idx = GetIdxST( node*2+1, l, mid, trgCount );
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    inverseSeq.resize(N, 0);
    ans.resize(N, 0);
    for ( int i = 0; i < N; i++ ){
        cin >> inverseSeq[i];
    }

    st.N = N;
    st.h = ceil(log2(st.N));
    st.size = (1<<(st.h+1)) - 1;
    st.arr.resize(st.size, 0);
    ConstructST( 0, 0, N-1);

    for ( int n = N; n > 0; n-- ){
        int count = inverseSeq[n-1] + 1;

        int idx = GetIdxST( 0, 0, N-1, count ) ;
        ans[idx] = n;
        AddST( 0, 0, N-1, idx, -1);

        // DEBUG
        // for ( auto val : ans )
        //     cout << val << " ";
        // cout << endl;
    }

    // Answer
    for ( auto val : ans )
        cout << val << " ";

    return 0;
}