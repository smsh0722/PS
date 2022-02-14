/* 1395 스위치
 * Lazy Propagation in Segment Tree
 * smsh0722
 * */
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

class SegmentTreeClass{
    public:
        SegmentTreeClass( const int N )
        {
            int h = (int)ceil( log2(N) );
            int size = (int)pow( 2, h + 1) - 1;
            ST = new int[size];
            lazy = new bool[size];
            memset( ST, 0, sizeof(int)*size );
            memset( lazy, 0, sizeof(bool)*size );
        }
        ~SegmentTreeClass()
        {
            delete[] ST;
            delete[] lazy;
        }
        int constructST( const int ti, const int li, const int ri, const bool arr[] );
        int updateRange( const int ti, const int li, const int ri, const int ql, const int qr );
        int getSum( const int ti, const int li, const int ri, const int ql, const int qr );
    private:
        int* ST;
        bool* lazy;
        void propagation( const int ti, const int li, const int ri );
};

/* ti: tree idx
 * li: left idx
 * ri: right idx
 * arr: elements arr
 * */
int SegmentTreeClass::constructST( const int ti, const int li, const int ri, const bool arr[] )
{
    /* Base case*/
    if ( li == ri ){
        ST[ti] = arr[li] == 1 ? (int)1 : (int)0;
        return ST[ti];
    }

    int mid = ( li + ri ) / 2;
    ST[ti] = constructST( ti*2+1, li, mid, arr )
                + constructST( ti*2+2, mid + 1, ri, arr );
    return ST[ti];
}
/* ql : query left 
 * qr : query right
 * diff : Add_val
 * */
int SegmentTreeClass::updateRange( const int ti, const int li, const int ri, const int ql, const int qr )
{
    /* lazy propagation */
    if ( lazy[ti] != 0 )
        propagation( ti, li, ri );

    /* case 1 : out of range */
    if ( qr < li || ri < ql ){
        return ST[ti];
    }
    /* case 2 : fully in range */
    if ( ql <= li && ri <= qr ){
        // update curr node
        ST[ti] = abs( (ri-li+1) - ST[ti] );
        // pass lazy to children
        if ( li != ri ){
            lazy[ti*2+1] = lazy[ti*2+1] == 0 ? 1 : 0;
            lazy[ti*2+2] = lazy[ti*2+2] == 0 ? 1 : 0;
        }
        return ST[ti];
    }
    /* case 3 : overlaps range */
    int mid = ( li + ri ) / 2;
    int left = updateRange( ti*2+1, li, mid, ql, qr );
    int right = updateRange( ti*2+2, mid+1, ri, ql, qr );
    ST[ti] = left + right;
    return ST[ti];
}
int SegmentTreeClass::getSum( const int ti, const int li, const int ri, const int ql, const int qr )
{  
    /* lazy propagation */
    if ( lazy[ti] != 0 )
        propagation( ti, li, ri );

    /* case 1 : out of range */
    if ( qr < li || ri < ql )
        return 0;
    /* case 2 : fully in range */
    if ( ql <= li && ri <= qr )
        return ST[ti];
    /* case 3 : overlaps reange */
    int mid = ( li + ri ) / 2;
    return getSum( ti*2+1, li, mid, ql, qr )
            + getSum( ti*2+2, mid+1, ri, ql, qr );
}
void SegmentTreeClass::propagation( const int ti, const int li, const int ri )
{
    // update current Node
    ST[ti] = abs( (ri - li + 1 ) - ST[ti] );
    // pass lazy to children
    if ( li != ri ){
        lazy[ti*2+1] = lazy[ti*2+1] == 0 ? 1 : 0;
        lazy[ti*2+2] = lazy[ti*2+2] == 0 ? 1 : 0;
    }
    // lazy reset
    lazy[ti] = 0;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N; // # of elements
    int M; // # of Query
    cin >> N >> M;

    bool offORon[N] = { 0 }; // 0: OFF, 1: ON

    /* Construct Segment Tree */
    SegmentTreeClass SegmentTree = SegmentTreeClass(N);
    SegmentTree.constructST( 0, 0, N - 1, offORon );

    /* Answer Query */
    int a, b, c;
    for ( int i = 0; i < M; i++ ){
        cin >> a >> b >> c;
        if ( a == 0 ) // reverse switch
            SegmentTree.updateRange( 0, 0, N - 1, b - 1, c - 1 );
        else{//( a == 1 ) Get sum arr[b-1~c-1]
            cout << SegmentTree.getSum( 0, 0, N - 1, b - 1, c - 1 ) << "\n";
        }
    }

    return 0;
}