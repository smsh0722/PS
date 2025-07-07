#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct DataST{
    int minH, maxH;
};

struct SegmentTree{
    vector<DataST> segmentTree;
    int h;
    int size;
};

const int MAX_INT = ~(1<<31);

SegmentTree st;
vector<int> cowH;
int N;
int Q;

inline int Max ( int a, int b ){ return a > b ? a : b; };
inline int Min ( int a, int b ){ return a < b ? a : b; };

DataST BuildST( int node, int l, int r );
DataST QueryST( int node, int l, int r, int tl, int tr );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    cowH.resize(N);
    for ( int i = 0; i < N; i++ ){
        cin >> cowH[i];
    }

    // Build ST
    st.h = ceil(log2(N));
    st.size = (1<<(st.h+1)) - 1;
    st.segmentTree.resize(st.size);
    BuildST(0, 0, N-1);

    // Ans Query
    for ( int i = 0; i < Q; i++ ){
        int l, r;
        cin >> l >> r;
        DataST rst = QueryST( 0, 0, N-1, l-1, r-1 );
        cout << rst.maxH - rst.minH << "\n";
    }

    return 0;
}

DataST BuildST( int node, int l, int r )
{
    if ( l == r ){
        int h = cowH[l];
        st.segmentTree[node] = DataST{ h, h};
        return st.segmentTree[node];
    }

    int mid = (r-l)/2 + l;
    DataST lRst = BuildST( node*2+1, l, mid );
    DataST rRst = BuildST( node*2+2, mid+1, r);

    DataST rst = DataST{ Min(lRst.minH, rRst.minH), Max( lRst.maxH, rRst.maxH) };

    st.segmentTree[node] = rst;
    return rst;
}
DataST QueryST( int node, int l, int r, int tl, int tr )
{
    if ( tl <= l && r <= tr ){
        return st.segmentTree[node];
    }
    if ( tr < l || r < tl )
        return DataST{MAX_INT, 0 };

    int mid = (r-l)/2+l;
    DataST lRst = QueryST( node*2+1, l, mid, tl, tr );
    DataST rRst = QueryST( node*2+2, mid+1, r, tl, tr);

    DataST rst = DataST{ Min(lRst.minH, rRst.minH)
                        , Max(lRst.maxH, rRst.maxH) };
    
    return rst;
}