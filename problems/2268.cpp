#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct SegTree{
    int h;
    int size;
    vector<int64_t> arr;
};

int N, M;
SegTree st;

int64_t GetST( int node, int l, int r, int tl, int tr )
{
    if ( tl <= l && r <= tr )
        return st.arr[node];
    if ( r < tl || tr < l )
        return 0;

    int mid = (r-l)/2 + l;
    return (GetST(node*2+1, l, mid, tl, tr ) + GetST( node*2+2, mid+1,r,tl,tr));
}

int64_t UpdateST( int node, int l, int r, int trg, int64_t val )
{
    if ( trg < l || r < trg )
        return st.arr[node];
    if ( l == r && l == trg )
        return (st.arr[node] = val);
    
    int mid = (r-l)/2+l;

    return (st.arr[node] = UpdateST(node*2+1, l, mid, trg, val )
                        + UpdateST(node*2+2, mid+1, r, trg, val ) );
}

int main( void  )
{   
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;

    st.h = ceil(log2(N));
    st.size = (1<<(st.h+1))-1;
    st.arr.resize(st.size, 0);
    
    for ( int m = 0; m < M; m++ ){
        int op, a, b;
        cin >> op >> a >> b;
        if ( op == 0 ){ // Sum
            if ( a > b )
                swap(a,b);
            cout << GetST(0, 0, N-1, a-1, b-1) << "\n";
        }
        else { // op == 1 : Modify
            UpdateST(0, 0, N-1, a-1, b );
        }
    }

    return 0;
}