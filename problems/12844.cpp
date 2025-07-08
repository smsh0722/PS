#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct SegTree {
    int size;
    int h;
    vector<int> arr;
    vector<int> lazy;
};

int N; // Num of Arr
int M; // Num of Qeury

SegTree st;
vector<int> seq;

int BuildST( int node, int l, int r);
void PropST(int node, int l, int r, int val );
int UpdateST( int node, int l, int r, int tl, int tr, int val );
int QueryST( int node, int l, int r, int tl, int tr );

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    seq.resize(N);
    for( int i = 0; i < N; i++ ){
        cin >> seq[i];
    }

    // Build ST
    st.h = ceil(log2(N));
    st.size = (1<<(st.h+1)) - 1;
    st.arr.resize(st.size);
    st.lazy.resize(st.size, 0);
    BuildST(0, 0, N-1);

    // Queries
    cin >> M;
    for ( int i = 0; i < M; i++ ){
        int option, tl, tr;
        cin >> option >> tl >> tr;
        if ( option == 1 ){// Update
            int val;
            cin >> val;
            UpdateST(0, 0, N-1, tl, tr, val );
        }
        else { // option == 2, print output
            cout << QueryST(0, 0, N-1, tl, tr ) << "\n";
        }
    }

    return 0;
}

int BuildST( int node, int l, int r )
{
    if ( l == r ){
        st.arr[node] = seq[l];
        return st.arr[node];
    }

    int mid = (r-l)/2+l;
    int lRst = BuildST( node*2+1, l, mid );
    int rRst = BuildST(node*2+2, mid+1, r);

    st.arr[node] = lRst ^ rRst;
    return st.arr[node];
}
void PropST(int node, int l, int r, int val )
{
    if ( (r-l+1) % 2 != 0 )
        st.arr[node] ^= val;
    if ( l < r ){
        st.lazy[node*2+1] ^= val;
        st.lazy[node*2+2] ^= val;
    }
    st.lazy[node] = 0;
}
int UpdateST( int node, int l, int r, int tl, int tr, int val )
{
    if ( st.lazy[node] != 0 ){
        // propagation
        PropST(node, l, r, st.lazy[node] );
    }
    if ( r < tl || tr < l )
        return st.arr[node];
    if ( tl <= l && r <= tr ){
        // propagation
        PropST(node, l, r, val );
        return st.arr[node];
    }

    int mid = (r-l)/2+l;
    int lRst = UpdateST(node*2+1, l, mid, tl, tr, val );
    int rRst = UpdateST(node*2+2, mid+1, r, tl, tr, val );

    st.arr[node] = lRst^rRst;
    return st.arr[node];
}
int QueryST( int node, int l, int r, int tl, int tr )
{
    if ( st.lazy[node] != 0 ){
        // propagation
        PropST(node, l, r, st.lazy[node] );
    }

    if ( r < tl || tr < l )
        return 0;
    if ( tl <= l && r <= tr ){
        return st.arr[node];
    }

    int mid = (r-l)/2+l;
    int lRst = QueryST(node*2+1, l, mid, tl, tr );
    int rRst = QueryST(node*2+2, mid+1, r,  tl, tr );

    return (lRst^rRst);
}