#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct ST{
    vector<int> segTree;
    int h;
    int size;
};

const int MAX_ID = 1000000;
int N;

ST st;
vector<int> A;
vector<int> dst(MAX_ID+1, -1);

int UpdateST( int node, int l, int r, int idx );
int QueryST( int node, int l, int r, int tl, int tr );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int64_t crossCount = 0;

    // Input
    cin >> N;
    A.resize(N);
    for ( int i = 0; i < N; i++ ){
        cin >> A[i];
    }
    for ( int i = 0; i < N; i++ ){
        int id;
        cin >> id;
        dst[id] = i;
    }

    // Build SegTree
    st.h = ceil(log2(N));
    st.size = (1<<(st.h+1))-1;
    st.segTree.resize(st.size, 0);

    // Calculate corssCount
    for ( int i = 0; i < N; i++ ){
        int id = A[i];
        int dstIdx = dst[id];
        crossCount += int64_t(QueryST( 0, 0, N-1, dstIdx+1, N-1));
        UpdateST(0, 0, N-1, dstIdx);
    }

    cout << crossCount;

    return 0;
}

int UpdateST( int node, int l, int r, int idx )
{
    if ( idx < l || r < idx ) 
        return st.segTree[node];
    if ( l == r && l == idx ){
        st.segTree[node] += 1;
        return st.segTree[node];
    }

    int mid = (r-l)/2 +l;
    int lRst = UpdateST(node*2+1, l, mid, idx);
    int rRst = UpdateST(node*2+2, mid+1, r, idx);

    st.segTree[node] = lRst + rRst;
    return st.segTree[node];
}

int QueryST( int node, int l, int r, int tl, int tr )
{
    if ( r < tl || tr < l )
        return 0;
    if  ( tl <= l && r <= tr )
        return st.segTree[node];

    int mid = (r-l)/2+l;
    int lRst = QueryST( node*2+1, l, mid, tl, tr );
    int rRst = QueryST(node*2+2, mid+1, r, tl, tr );

    return (lRst+rRst);
}