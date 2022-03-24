/* smsh0722
 * 2580
 * 스도쿠
 * */
#include <iostream>
#include <cstring>
using namespace std;

int board[9][9];
bool row[9][10];
bool column[9][10];
bool box[3][3][10];

bool solve_sudoku( int blanks[81][2], int blanks_size, int idx );
/*
bool checkBox( int curR, int curC );
bool checkRow( int curR );
bool checkColumn( int curC );
*/
int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int blanks[81][2];
    int blanks_size = 0;

    for ( int i = 0; i < 9; i++ ){
        memset( row[i], 0, 10 );
        memset( column[i], 0, 10 );
    }
    for ( int i = 0; i < 3; i++ ){
        for ( int j = 0; j < 3; j++ )
            memset( box[i][j], 0, 10 );
    }

    for ( int r = 0; r < 9; r++ ){
        for ( int c = 0; c < 9; c++ ){
            cin >> board[r][c];
            
            row[r][board[r][c]] = true;
            column[c][board[r][c]] = true;
            box[r/3][c/3][board[r][c]] = true;

            if ( board[r][c] == 0 ){
                blanks[blanks_size][0] = r;
                blanks[blanks_size][1] = c;
                blanks_size++;
            }
        }
    }

    // solve
    solve_sudoku( blanks, blanks_size, 0 );

    // Print result
    for ( int r = 0; r < 9; r++ ){
        for ( int c = 0; c < 9; c++ )
            cout << board[r][c] << " ";
        cout << "\n";
    }
}

bool solve_sudoku( int blanks[81][2], int blanks_size, int idx )
{
    int curR = blanks[idx][0];
    int curC = blanks[idx][1];

    for ( int i = 1; i <= 9; i++ ){
        // Check tmp answer
        if ( ( row[curR][i] || column[curC][i] || box[curR/3][curC/3][i] ) == true )
            continue;
        
        row[curR][i] = true;
        column[curC][i] = true;
        box[curR/3][curC/3][i] = true;
        board[curR][curC] = i; // Temp ans

        // Solve next Blanks
        if ( idx + 1 == blanks_size )
            return true;
        else if ( solve_sudoku( blanks, blanks_size, idx + 1 ) == true )
            return true;

        row[curR][i] = false;
        column[curC][i] = false;
        box[curR/3][curC/3][i] = false;
    }

    board[curR][curC] = 0; // Reset to 0

    return false;
}
/*
bool checkBox( int curR, int curC )
{
    int sR = (curR / 3)*3; // start row {0, 3, 6}
    int sC = (curC / 3)*3; // start Column {0, 3, 6}

    bool flag[10] = {0};
    for ( int r = 0; r < 3; r++ ){
        for ( int c = 0; c < 3; c++ ){
            int trgVal = board[sR+r][sC+c];

            if ( trgVal == 0 )
                continue;
            if ( flag[trgVal] == true )
                return false;

            flag[trgVal] = true;
        }
    }

    return true;
}
bool checkRow( int curR )
{
    bool flag[10] = {false};
    for ( int c = 0; c < 9; c++ ){
        int trgVal = board[curR][c];

        if ( trgVal == 0 )
            continue;
        if ( flag[trgVal] == true )
            return false;
        
        flag[trgVal] = true;
    }
    return true;
}
bool checkColumn( int curC )
{
    bool flag[10] = {false};
    for ( int r = 0; r < 9; r++ ){
        int trgVal = board[r][curC];

        if ( trgVal == 0 )
            continue;
        if ( flag[trgVal] == true )
            return false;
        
        flag[trgVal] = true;
    }

    return true;
}
*/