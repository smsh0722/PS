/* 1275 커피숍
 * Segment Tree
 * smsh0722
 * */

#include <iostream>
#include <cmath>
using namespace std;

/* ST: Segment Tree
 * ti: tree idx (ST)
 * li: left idx (arr)
 * ri: right idx (arr)
 * */
int64_t constructST( int64_t ST[], const int ti, const int li, const int ri, const int arr[] )
{
    /* base */
    if ( li == ri ){
        ST[ti] = arr[li];
        return ST[ti];
    }

    /* DFS */
    {
        int mid = (li+ri) / 2;
        int lc = ti * 2 + 1; // left child
        int rc = ti * 2 + 2; // right child
        ST[ti] = constructST( ST, lc, li, mid, arr ) + constructST( ST, rc, mid+1, ri, arr );
    }
    return ST[ti];
}
void updateST( int64_t ST[], const int ti, const int li, const int ri, const int trgIdx, const int64_t gap )
{
    ST[ti] += gap;
    if ( li == ri )
        return;

    int mid = ( li + ri ) / 2;
    if ( trgIdx >= li && trgIdx <= mid )
        updateST( ST, ti*2+1, li, mid, trgIdx, gap );
    else if ( trgIdx >= mid+1 && trgIdx <= ri )
        updateST( ST, ti*2+2, mid+1, ri, trgIdx, gap );
}
int64_t calSum( int64_t ST[], const int ti, const int li, const int ri, const int ql, const int qr )
{
    if ( ql <= li && ri <= qr )
        return (int64_t)ST[ti];

    if ( ql > ri || qr < li )
        return 0;

    int mid = (li+ri)/2;
    return calSum(ST, ti*2+1, li, mid, ql, qr ) +
            calSum(ST, ti*2+2, mid+1, ri, ql, qr );   
}
int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int N, Q;
    cin >> N >> Q;

    int arr[N];
    for ( int i = 0; i < N; i++ )
        cin >> arr[i];
    
    int64_t* ST; // Segment Tree
    /* construct segment tree */
    {
        int h = (int)ceil(log2(N));
        int size = 2 * (int)pow(2, h) - 1;
        ST = new int64_t[size];
        constructST( ST, 0, 0, N - 1, arr );
    }

    int x, y, a, b;
    for ( int i = 0; i < Q; i++ ){
        cin >> x >> y >> a >> b;
        if ( x > y ){
            int tmp = x;
            x = y;
            y = tmp;
        }
        cout << calSum( ST, 0, 0, N - 1, x - 1, y - 1 ) << "\n";
        int64_t gap = b - (int64_t)arr[a-1];
        arr[a-1] = b;
        updateST( ST, 0, 0, N - 1, a - 1, gap );
    }

    delete[] ST;
    return 0;
}
