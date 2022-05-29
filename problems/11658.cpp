/* smsh0722
 * 11658
 * 구간 합 구하기3
 * */
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int N; // size of row and column
int M; // # of Operation

struct Point{
    int r;
    int c;
};

class SegmentTree2D {
    public:
        SegmentTree2D( int N );
        void construct2D( int cIdx, int l, int r, int** val_matrix );
        void construct( int rIdx, int cIdx, int l, int r, int c, int** val_matrix );
        void update2D( int cIdx, Point s, Point e, Point trg, int diff );
        void update( int rIdx, int cIdx, int s, int e, int trg, int diff );
        int getSum2D( int cIdx, Point s, Point e, Point trgS, Point trgE );
        int getSum( int rIdx, int cIdx, int s, int e, int trgS, int trgE );
    private:
        int** ST;
        int size;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;

    int** val_matrix;
    // Construct value matrix
    {
        val_matrix = new int*[N];
        for ( int i = 0; i < N; i++ ){
            val_matrix[i] = new int[N];
        }

        for ( int r = 0; r < N; r++ ){
            for ( int c = 0; c < N; c++ )
                cin >> val_matrix[r][c];
        }
    }

    SegmentTree2D ST2D(N);

    // Construct 2D Segment Tree 
    ST2D.construct2D( 0, 0, N-1, val_matrix );

    // Solve
    for ( int qIdx = 0; qIdx < M; qIdx++ ){
        int w;
        cin >> w;
        if ( w == 0 ){ // Update
            int r, c, val;
            cin >> r >> c >> val;

            r--; c--;

            ST2D.update2D( 0, Point{0,0}, Point{N-1,N-1}, Point{r,c}, val - val_matrix[r][c] );

            val_matrix[r][c] = val;
        }
        else { // w == 1, Get Sum
            int p, q, r, s;
            cin >> p >> q >> r >> s;

            p--; q--; r--;s--;

            cout << ST2D.getSum2D( 0, Point{0,0}, Point{N-1, N-1}, Point{p,q}, Point{r,s} ) << "\n";
        }
    }

    return 0;
}

SegmentTree2D::SegmentTree2D( int N )
{
    int h = ceil(log2(N));
    size = (1<<(h+1))-1;

    ST = new int*[size];
    for ( int i = 0 ;i < size; i++ ){
        ST[i] = new int[size];
        memset( ST[i], 0, sizeof(int) * size);
    }
}
void SegmentTree2D::construct2D( int cIdx, int l, int r, int** val_matrix )
{
    if ( l == r )
        construct( 0, cIdx, 0, N-1, l, val_matrix );
    else {
        int mid = (r-l)/2+l;
        construct2D( cIdx*2+1, l, mid, val_matrix );
        construct2D( cIdx*2+2, mid+1, r, val_matrix );

        // Merge       
        for ( int r = 0; r < size; r++ )
            ST[r][cIdx] = ST[r][cIdx*2+1] + ST[r][cIdx*2+2];
    }
}
void SegmentTree2D::construct( int rIdx, int cIdx, int l, int r, int c, int** val_matrix )
{
    if ( l == r )
        ST[rIdx][cIdx] = val_matrix[l][c];
    else {
        int mid = ( r - l )/ 2 + l;
        construct( rIdx*2+1, cIdx, l, mid, c, val_matrix );
        construct( rIdx*2+2, cIdx, mid+1, r, c, val_matrix );

        ST[rIdx][cIdx] = ST[rIdx*2+1][cIdx] + ST[rIdx*2+2][cIdx];
    }
}
void SegmentTree2D::update2D( int cIdx, Point s, Point e, Point trg, int diff )
{
    if( trg.c < s.c || e.c < trg.c )
        return;

    update( 0, cIdx, s.r, e.r, trg.r, diff );
    if ( s.c != e.c ){
        int mid_c = (e.c-s.c)/2 + s.c;
        update2D( cIdx*2+1, s, Point{e.r, mid_c}, trg, diff );
        update2D( cIdx*2+2, Point{s.r, mid_c+1}, e, trg, diff );
    }
}
void SegmentTree2D::update( int rIdx, int cIdx, int s, int e, int trg, int diff )
{
    if ( trg < s || e < trg )
        return;
    
    ST[rIdx][cIdx] += diff;
    if ( s != e ) {
        int mid = ( e - s )/2 + s;
        update( rIdx*2+1, cIdx, s, mid, trg, diff );
        update( rIdx*2+2, cIdx, mid + 1, e, trg, diff );
    }
}
int SegmentTree2D::getSum2D( int cIdx, Point s, Point e, Point trgS, Point trgE )
{
    if ( trgS.c <= s.c && e.c <= trgE.c )
        return getSum( 0, cIdx, s.r, e.r, trgS.r, trgE.r );
    if ( trgE.c < s.c || e.c < trgS.c )
        return 0;

    int mid_c = (e.c-s.c)/2 +s.c;
    int lval = getSum2D( cIdx*2+1, s, Point{e.r, mid_c}, trgS, trgE );
    int rval = getSum2D( cIdx*2+2, Point{s.r,mid_c+1}, e, trgS, trgE );
    return (lval+rval);
}
int SegmentTree2D::getSum( int rIdx, int cIdx, int s, int e, int trgS, int trgE )
{
    if ( trgS <= s && e <= trgE )
        return ST[rIdx][cIdx];
    if ( trgE < s || e < trgS )
        return 0;
    
    int mid = (e-s)/2 + s;
    int lval = getSum( rIdx*2+1, cIdx, s, mid, trgS, trgE );
    int rval = getSum( rIdx*2+2, cIdx, mid+1, e, trgS, trgE );
    return (lval+rval);
}