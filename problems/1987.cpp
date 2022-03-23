/* smsh0722
 * 1987
 * 알파벳
 * */
#include <iostream>
using namespace std;

char** board;
int ROWSIZE;
int COLUMNSIZE;

/* Search all possible routes
 * r = current row
 * c = current column
 * seqBits = binary Flag for each alphabet
 * count = current count
 * */
int moveDFS( int r, int c, int seqBits, int count );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> ROWSIZE >> COLUMNSIZE;

    board = new char*[ROWSIZE];
    for ( int i = 0; i < ROWSIZE; i++ ){
        board[i] = new char[COLUMNSIZE];
        // Input
        for ( int j = 0; j < COLUMNSIZE; j++ )
            cin >> board[i][j];
    }
    
    int start_bits = 1<<(board[0][0]-'A');
    cout << moveDFS( 0, 0, start_bits, 1 );

    return 0;
}

int moveDFS( int r, int c, int seqBits, int count )
{
    // cout << r << ", " << c << " = " << count << endl; // Debug
    // DFS
    int max = count;

    int nextPos[4][2];
    nextPos[0][0] = r - 1; nextPos[0][1] = c;
    nextPos[1][0] = r + 1; nextPos[1][1] = c;
    nextPos[2][0] = r;     nextPos[2][1] = c - 1;
    nextPos[3][0] = r;     nextPos[3][1] = c + 1;

    for ( int i = 0; i < 4; i++ ){
        int nextR = nextPos[i][0];
        int nextC = nextPos[i][1];
        if ( nextR < 0 || nextR >= ROWSIZE )
            continue;
        if ( nextC < 0 || nextC >= COLUMNSIZE )
            continue;
        
        int nextCharBits = 1 << ( board[nextR][nextC] - 'A' );
        if ( (seqBits&nextCharBits) != 0 )
            continue;
        
        int tmp = moveDFS( nextR, nextC, seqBits|nextCharBits, count + 1 );
        max = max < tmp ? tmp : max;
    }

    // return rst
    return max;
}