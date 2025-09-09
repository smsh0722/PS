#include <iostream>
#include <vector>
using namespace std;

const int ROW = 3;
const int COL = 3;

int board[ROW][COL];

inline int GetRowWinner( int r )
{
    int winner = board[r][0];
    for ( int c = 1; c < COL; c++ ){
        if ( winner != board[r][c] )
            winner = -1;
    }

    return winner;
}
inline int GetColWinner( int c )
{
    int winner = board[0][c];
    for ( int r = 1; r < ROW; r++ ){
        if ( winner != board[r][c] )
            winner = -1;
    }

    return winner;
}
inline int GetDiagonal1Winner(int r, int c)
{
    if ( r != c )
        return -1;

    int winner = board[0][0];
    for ( int i = 1; i < ROW; i++ ){
        if ( winner != board[i][i] )
            winner = -1;
    }
    return winner;
}
inline int GetDiagonal2Winner( int r, int c)
{
    if ( (r+c) != 2 )
        return -1;

    int winner = board[0][2];
    for ( int i = 1; i < ROW; i++ ){
        if ( winner != board[i][ROW-1-i] )
            winner = -1;
    }
    return winner;
}

inline void PrintBoard()
{
    cout << "-------------------------\n";
    for ( int r = 0; r < ROW; r++ ){
        for ( int c = 0; c < COL; c++ ){
            cout << board[r][c] << " ";
        } cout << endl;
    }
}
int SearchAllGameRecursive( int player, int leftCount )
{
    if ( leftCount == 0 ){
        return 0;
    }   

    bool bExistDraw = false;
    int nextLeftCount = leftCount - 1;
    int nextPlayer = (player*2)%3;
    for ( int r = 0; r < ROW; r++ ){
        for ( int c = 0; c < COL; c++ ){
            if ( board[r][c] != 0 )
                continue;

            // Try this case
            board[r][c] = player;

            // printf("leftCount: %d", leftCount);// DEBUG
            // PrintBoard(); // DEBUG

            // Check Winner
            // row check
            if ( player == GetRowWinner(r) ||
                player == GetColWinner(c) || 
                player == GetDiagonal1Winner(r, c) ||
                player == GetDiagonal2Winner(r, c) )
            {
                board[r][c] = 0;
                return player;
            }

            int tmpWinner = SearchAllGameRecursive( nextPlayer, nextLeftCount );
            if ( tmpWinner == player ){
                board[r][c] = 0;
                return player;
            }
            else if ( tmpWinner == 0 )
                bExistDraw = true;

            // Rollback
            board[r][c] = 0;
        }
    }

    if ( bExistDraw == true )
        return 0;
    else 
        return nextPlayer;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    int leftCount = 0;
    int p1Count = 0;
    int p2Count = 0;
    for ( int r = 0; r < ROW; r++ ){
        for ( int c = 0; c < COL; c++ ){
            cin >> board[r][c];
            if ( board[r][c] == 0 )
                leftCount++;
            else if ( board[r][c] == 1 )
                p1Count++;
            else 
                p2Count++;
        }
    }

    int nextPlayer = p1Count == p2Count ? 1 : 2;
    // cout << "nextPlayer: " << nextPlayer << endl; // DEBUG
    int winner = SearchAllGameRecursive( nextPlayer, leftCount );

    if ( winner == 0 )
        cout << "D";
    else if ( winner == nextPlayer )
        cout << "W";
    else 
        cout << "L";
    return 0;
}