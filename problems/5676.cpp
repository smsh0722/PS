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

const int MAX_N = 100000;

// Len of sequence
int N;
// # of Queries
int K;

SegTree st;

int UpdateST( int node, int l, int r, int trg, int val )
{
    if ( trg < l || r < trg )
        return st.arr[node];
    if ( l == trg && trg == r )
        return st.arr[node] = val;

    int mid = ( r - l ) / 2 + l;
    int lRst = UpdateST(node*2+1, l, mid, trg, val );
    int rRst = UpdateST(node*2+2, mid+1, r, trg, val );

    return st.arr[node] = lRst*rRst;
}

int GetST( int node, int l, int r, int tl, int tr )
{
    if ( tr < l || r < tl )
        return 1;
    if ( tl <= l && r <= tr )
        return st.arr[node];

    int mid = (r-l)/2+l;
    return GetST( node*2+1, l, mid, tl, tr ) * GetST(node*2+2, mid+1,r,tl,tr);
}

inline int Norm( int a )
{
    if ( a > 0 )
        return 1;
    else if  (a < 0 )
        return -1;
    else 
        return 0;
}
int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    st.N = MAX_N;
    st.h = ceil(log2(st.N));
    st.size = (1<<(st.h+1))-1;
    st.arr.resize(st.size, 0 );

    while ( cin >> N ){
        cin >> K;
        for ( int ni = 0; ni < N; ni++ ){
            int val;
            cin >> val;
            
            UpdateST(0, 0, st.N-1, ni, Norm(val) );
        }
        // cout << "here\n";//Debug
        for ( int k = 0; k < K; k++ ){
            char opt;
            int a, b;
            cin >> opt >> a >> b;

            // cout << "ki: " <<k << endl;// DEBUG
            if ( opt == 'C' ){
                UpdateST(0,0,st.N-1, a-1, Norm(b));
            }
            else { // opt == 'P'
                int rst = GetST( 0, 0, st.N-1, a-1, b-1 );
                if ( rst > 0 )
                    cout << "+";
                else if ( rst < 0 )
                    cout << "-";
                else 
                    cout << 0;
            }
        }

        cout << "\n";
    }

    return 0;
}