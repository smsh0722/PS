/* 10999 구간 합 구하기2
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
            ST = new int64_t[size];
            lazy = new int64_t[size];
            memset( ST, 0, sizeof(int64_t)*size );
            memset( lazy, 0, sizeof(int64_t)*size );
        }
        ~SegmentTreeClass()
        {
            delete[] ST;
            delete[] lazy;
        }
        int64_t constructST( const int64_t ti, const int64_t li, const int64_t ri, const int64_t arr[] );
        int64_t updateRange( const int64_t ti, const int64_t li, const int64_t ri, const int64_t ql, const int64_t qr, const int64_t diff );
        int64_t getSum( const int64_t ti, const int64_t li, const int64_t ri, const int64_t ql, const int64_t qr );
    private:
        int64_t* ST;
        int64_t* lazy;
        void propagation( const int64_t ti, const int64_t li, const int64_t ri );
};

/* ti: tree idx
 * li: left idx
 * ri: right idx
 * arr: elements arr
 * */
int64_t SegmentTreeClass::constructST( const int64_t ti, const int64_t li, const int64_t ri, const int64_t arr[] )
{
    /* Base case*/
    if ( li == ri ){
        ST[ti] = arr[li];
        return ST[ti];
    }

    int64_t mid = ( li + ri ) / 2;
    ST[ti] = constructST( ti*2+1, li, mid, arr )
                + constructST( ti*2+2, mid + 1, ri, arr );
    return ST[ti];
}
/* ql : query left 
 * qr : query right
 * diff : Add_val
 * */
int64_t SegmentTreeClass::updateRange( const int64_t ti, const int64_t li, const int64_t ri, const int64_t ql, const int64_t qr, const int64_t diff )
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
        ST[ti] += ( ri - li + 1 ) * diff;
        // pass lazy to children
        if ( li != ri ){
            lazy[ti*2+1] += diff;
            lazy[ti*2+2] += diff;
        }
        return ST[ti];
    }
    /* case 3 : overlaps range */
    int64_t mid = ( li + ri ) / 2;
    int64_t left = updateRange( ti*2+1, li, mid, ql, qr, diff );
    int64_t right = updateRange( ti*2+2, mid+1, ri, ql, qr, diff );
    ST[ti] = left + right;
    return ST[ti];
}
int64_t SegmentTreeClass::getSum( const int64_t ti, const int64_t li, const int64_t ri, const int64_t ql, const int64_t qr )
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
    int64_t mid = ( li + ri ) / 2;
    return getSum( ti*2+1, li, mid, ql, qr )
            + getSum( ti*2+2, mid+1, ri, ql, qr );
}
void SegmentTreeClass::propagation( const int64_t ti, const int64_t li, const int64_t ri )
{
    // update current Node
    ST[ti] += (ri - li + 1) * lazy[ti];
    // pass lazy to children
    if ( li != ri ){
        lazy[ti*2+1] += lazy[ti];
        lazy[ti*2+2] += lazy[ti];
    }
    // lazy reset
    lazy[ti] = 0;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N; // # of elements
    int M; // # of update Query
    int K; // # of sum Query
    cin >> N >> M >> K;

    int64_t arr[N];
    for ( int i = 0; i < N; i++ )
        cin >> arr[i];

    /* Construct Segment Tree */
    SegmentTreeClass SegmentTree = SegmentTreeClass(N);
    SegmentTree.constructST( 0, 0, N - 1, arr );

    /* Answer Query */
    int64_t a, b, c, d;
    for ( int i = 0; i < M + K; i++ ){
        cin >> a;
        if ( a == 1 ){ // Add d arr[b-1~c-1]
            cin >> b >> c >> d;
            SegmentTree.updateRange( 0, 0, N - 1, b - 1, c - 1, d );
        }
        else{//( a == 2 ) Get sum arr[b-1~c-1]
            cin >> b >> c;
            cout << SegmentTree.getSum( 0, 0, N - 1, b - 1, c - 1 ) << "\n";
        }
    }

    return 0;
}