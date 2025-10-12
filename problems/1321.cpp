#include <iostream>
#include <vector>
#include <cmath>

using namespace std;

struct SegTree{
    int h;
    int size;
    vector<int> arr;
};

// # of groups
int N;
// # of queries
int M;

SegTree st;

int BuildST( int node, int l, int r, const vector<int>& arr )
{
    if ( l == r ){
        return st.arr[node] = arr[l];
    }

    int mid = ( r - l )/ 2 + l;

    return (st.arr[node] = BuildST(node*2+1, l, mid, arr ) + BuildST(node*2+2, mid+1, r, arr));
}

int AddSegTree( int node, int l, int r, int trg, int val )
{
    if ( trg < l || r < trg )
        return st.arr[node];
    if ( l == r && l == trg )
        return st.arr[node] += val;
    
    int mid = (r-l)/2 + l;

    return (st.arr[node] = AddSegTree(node*2+1, l, mid, trg, val ) + AddSegTree( node*2+2, mid+1, r, trg, val ));
}
int AnsSegTree( int node, int l, int r, int val )
{
    if ( l == r )
        return l;
    
    int mid = (r-l)/2 + l;
    int left = st.arr[node*2+1];
    if ( left < val ){ // soldier in right range
        return AnsSegTree(node*2+2, mid+1, r, val - left );
    }
    else {//left >= val // soldier in left range
        return AnsSegTree(node*2+1, l, mid, val );
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    {
        vector<int> groups(N+1, 0);
        for ( int i = 1; i <= N; i++ )
            cin >> groups[i];
        st.h = ceil(log2(N));
        st.size = (1<<(st.h+1))-1;
        st.arr.resize(st.size,0);
        BuildST( 0, 0, N, groups);
    }

    cin >> M;
    for ( int mi = 0; mi < M; mi++ ){
        int query;
        cin >> query;
        if ( query == 1 ){
            int i, a;
            cin >> i >> a;
            AddSegTree( 0, 0, N, i, a );
        }
        else { // query == 2
            int i;
            cin >> i;

            cout << AnsSegTree(0, 0, N, i) << "\n";
        }
    }

    return 0;
}