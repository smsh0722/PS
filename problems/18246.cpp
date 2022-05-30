/* smsh0722
 * 18246
 * 색종이와 쿼리
 * */
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int N; // # of Paper
int M; // # of Query

const int RANGE = 1500;

int maxOf2( int a, int b );
void printBoard( int** board, int N );

struct Point{
    int r;
    int c;
};

class SegmentTree2D {
    public:
        SegmentTree2D( int RANGE );
        void construct2D( int cIdx, int l, int r, int** val_matrix );
        void construct( int rIdx, int cIdx, int l, int r, int c, int** val_matrix );
        int getMax2D( int cIdx, Point s, Point e, Point trgS, Point trgE );
        int getMax( int rIdx, int cIdx, int s, int e, int trgS, int trgE );
    private:
        int** ST;
        int size;
        int RANGE;
};

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;

    int** board;
    {
        board = new int*[RANGE];
        for ( int r = 0; r < RANGE; r++){
            board[r] = new int[RANGE];
            memset( board[r], 0, sizeof(int)*(RANGE) );
        }
    }
    
    // Input
    {
        int r1, c1, r2, c2;
        for ( int i = 0; i < N; i++ ){
            cin >> r1 >> c1 >> r2 >> c2;

            board[r1][c1] += 1;
            if ( c2 < RANGE )
                board[r1][c2] -= 1;
            if ( r2 < RANGE )
                board[r2][c1] -= 1;
            if ( ( r2 < RANGE ) && ( c2 < RANGE ) )
                board[r2][c2] += 1;
        }
    }

    // Preprocessing
    {
        for ( int r = 0; r < RANGE; r++ ){
            for ( int c = 1; c < RANGE; c++ )
                board[r][c] += board[r][c-1];
        }
        for ( int c = 0; c < RANGE; c++ ){
            for ( int r = 1; r < RANGE; r++ )
                board[r][c] += board[r-1][c];
        }
    }

    /* Debug
     * print 10x10 board
     * */
    // printBoard( board, 10 );

    SegmentTree2D ST2D(RANGE);
    ST2D.construct2D( 0, 0, RANGE-1, board );

    // Solve
    {
        int y1, x1, y2, x2;
        for ( int i = 0; i < M; i++ ){
            cin >> y1 >> x1 >> y2 >> x2;
            
            cout << ST2D.getMax2D( 0, Point{0,0}, Point{RANGE-1, RANGE-1}, Point{y1,x1}, Point{y2-1,x2-1} ) << "\n";
        }
    }

    return 0;
}

SegmentTree2D::SegmentTree2D( int RANGE )
{
    int h = ceil(log2(RANGE));
    size = (1<<(h+1))-1;

    ST = new int*[size];
    for ( int i = 0 ;i < size; i++ ){
        ST[i] = new int[size];
        memset( ST[i], 0, sizeof(int) * size);
    }

    this->RANGE = RANGE;
}
void SegmentTree2D::construct2D( int cIdx, int l, int r, int** val_matrix )
{
    if ( l == r )
        construct( 0, cIdx, 0, RANGE-1, l, val_matrix );
    else {
        int mid = (r-l)/2+l;
        construct2D( cIdx*2+1, l, mid, val_matrix );
        construct2D( cIdx*2+2, mid+1, r, val_matrix );

        // Merge       
        for ( int rIdx = 0; rIdx < size; rIdx++ )
            ST[rIdx][cIdx] = maxOf2( ST[rIdx][cIdx*2+1], ST[rIdx][cIdx*2+2] );
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

        ST[rIdx][cIdx] = maxOf2( ST[rIdx*2+1][cIdx], ST[rIdx*2+2][cIdx] );
    }
}
int SegmentTree2D::getMax2D( int cIdx, Point s, Point e, Point trgS, Point trgE )
{
    if ( trgS.c <= s.c && e.c <= trgE.c ){
        int val = ST[0][cIdx];
        return getMax( 0, cIdx, s.r, e.r, trgS.r, trgE.r );
    }
    if ( trgE.c < s.c || e.c < trgS.c )
        return 0;

    int mid_c = (e.c-s.c)/2 +s.c;
    int lval = getMax2D( cIdx*2+1, s, Point{e.r, mid_c}, trgS, trgE );
    int rval = getMax2D( cIdx*2+2, Point{s.r,mid_c+1}, e, trgS, trgE );

    return maxOf2( lval, rval );
}
int SegmentTree2D::getMax( int rIdx, int cIdx, int s, int e, int trgS, int trgE )
{
    if ( trgS <= s && e <= trgE )
        return ST[rIdx][cIdx];
    if ( trgE < s || e < trgS )
        return 0;
    
    int mid = (e-s)/2 + s;
    int lval = getMax( rIdx*2+1, cIdx, s, mid, trgS, trgE );
    int rval = getMax( rIdx*2+2, cIdx, mid+1, e, trgS, trgE );

    return maxOf2(lval, rval);
}
int maxOf2( int a, int b )
{
    if ( a > b )
        return a;
    return b;
}
void printBoard( int** board, int N )
{
    for ( int  r = 0; r < N; r++ ){
        for ( int c = 0; c < N; c++ )
            cout << board[r][c] << " ";
        cout << "\n";   
    }
}