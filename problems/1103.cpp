/* smsh0722
 * 1103
 * 게임
 * */
#include <iostream>
#include <cstring>
using namespace std;

int N, M;

struct Position{
    int r, c;
};

int DFS( char** board, bool** recStack, int r, int c, int** dp );
void getAdjCell( int moveSize, int r, int c, Position* adjCell );

int main( void )
{
    cin >> N >> M;

    /* Store board
     * 1 ~ 9: size of movement
     * H: hole
     * */
    char** board;

    // Input
    {
        board = new char*[N];
        for ( int r = 0; r < N; r++ )
            board[r] = new char[M];
        
        for ( int r = 0; r < N; r++ ){
            for ( int c = 0; c < M; c++ )
                cin >> board[r][c];
        }
    }

    /* Store Dynamic Programming Result */
    int** dp;

    // Solve
    {   
        /* DFS recursion Stack
         * Store flags of each Cell
         * */
        bool** recStack;

        // Dynamic Allocation( recStack )
        {
            recStack = new bool*[N];
            for( int r = 0; r < N; r++ ){
                recStack[r] = new bool[M];
                memset( recStack[r], false, sizeof(bool)*M );
            }
        }
        
        // Dynamic Allocation( dp )
        {
            dp = new int*[N];
            for ( int r = 0; r < N; r++ ){
                dp[r] = new int[M];
                memset( dp[r], 0, sizeof(int)*M );
            }
        }

        // DFS
        DFS( board, recStack, 0, 0, dp );

        // Avoid mem leaks
        for ( int r = 0; r < N; r++ )
            delete[] recStack[r];
        delete[] recStack;
    }
    
    // Print Answer
    cout << dp[0][0];

    return 0;
}
int DFS( char** board, bool** recStack, int r, int c, int** dp )
{
    // push current Cell to recStack
    recStack[r][c] = true;

    // Store Next position
    Position adjCell[4];
    getAdjCell( board[r][c] - '0', r, c, adjCell );

    /* max from next Position
     * 0 if next Pos is end
     * else 1 or more
     * */
    int max = 0;
    for ( int i = 0; i < 4; i++ ){
        int rst = 0;
        if ( adjCell[i].r >= 0 && adjCell[i].r < N && adjCell[i].c >= 0 && adjCell[i].c < M ){
            // Check Cycle
            if ( recStack[adjCell[i].r][adjCell[i].c] == true ){
                dp[r][c] = -1;
                return -1;
            }

            // Check Hole
            if ( board[adjCell[i].r][adjCell[i].c] == 'H' )
                rst = 0;
            // Else dp or DFS
            else if ( dp[adjCell[i].r][adjCell[i].c] == 0 ){
                if ( ( rst = DFS( board, recStack, adjCell[i].r, adjCell[i].c, dp ) ) == -1 ){
                    dp[r][c] = -1;
                    return -1;
                }
            }
            else
                rst = dp[adjCell[i].r][adjCell[i].c];
        }

        max = max > rst ? max : rst;
    }

    // max + cur move(1)
    dp[r][c] = max + 1; 
    
    // Pop current Cell from recStack
    recStack[r][c] = false;

    return dp[r][c];
}
void getAdjCell( int moveSize, int r, int c, Position* adjCell )
{
    adjCell[0].r = r - moveSize; adjCell[0].c = c;
    adjCell[1].r = r + moveSize; adjCell[1].c = c;
    adjCell[2].r = r;            adjCell[2].c = c - moveSize;
    adjCell[3].r = r;            adjCell[3].c = c + moveSize;
}