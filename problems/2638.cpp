/* smsh0722
 * 2638
 * 치즈
 * */
#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

enum condition{
    VISITED = -1,
    EMPTY,
    CHEESE
};

/* r == row
 * c == column
 * time == visited time
 * */
struct Node{
    int r;
    int c;
    int time;
};

int main( void )
{
    ios_base::sync_with_stdio( false ); cin.tie(NULL);

    int N;
    int M;
    cin >> N >> M;

    /* Store current board
     * 0 == empty
     * 1 == cheese
     * -1 == visited
     * */
    condition** board = new condition*[N];

    /* Store # of air-contact surfaces of each cheese
     * 0 ~ n == # of air-contact surfaces
     * */
    int** contact_count = new int*[N];
    
    // Input
    for ( int r = 0; r < N; r++ ){
        board[r] = new condition[M];
        for ( int c = 0; c < M; c++ ){ // Input
            int val;
            cin >> val;
            board[r][c] = (condition)val;
        }

        contact_count[r] = new int[M];
        memset( contact_count[r], 0, sizeof(int) * M );
    }

    int estimated_time = 0; // Answer

    /* Queue for current time*/
    queue<Node>* curQ = new queue<Node>;
    /* Queue for next time */
    queue<Node>* nextQ = new queue<Node>;

    // First Push
    curQ->push( {0, 0, 0} ); board[0][0] = VISITED;
    // BFS
    while ( curQ->empty() == false ){
        Node curNode = curQ->front(); curQ->pop();
        
        estimated_time += ( curNode.time - estimated_time );
        
        int adjCell[4][2]; // 4 x {r, c}
        adjCell[0][0] = curNode.r - 1; adjCell[0][1] = curNode.c;       // Up
        adjCell[1][0] = curNode.r + 1; adjCell[1][1] = curNode.c;       // Down
        adjCell[2][0] = curNode.r;     adjCell[2][1] = curNode.c - 1;   // Left
        adjCell[3][0] = curNode.r;     adjCell[3][1] = curNode.c + 1;   // Right

        for ( int i = 0; i < 4; i++ ){
            int trgR = adjCell[i][0];
            int trgC = adjCell[i][1];

            // OutOfRange
            if ( trgR < 0 || trgR >= N )
                continue;
            if ( trgC < 0 || trgC >= M )
                continue;
            // Already Calculated cell
            if ( board[trgR][trgC] == VISITED )
                continue;
            
            // AdjAir
            if ( board[trgR][trgC] == EMPTY ){
                curQ->push( {trgR, trgC, curNode.time} );
                board[trgR][trgC] = VISITED;
            }
            // AdjCheese
            else if ( board[trgR][trgC] == CHEESE ){
                contact_count[trgR][trgC]++;
                
                // Melt
                if ( contact_count[trgR][trgC] >= 2 ){
                    nextQ->push( { trgR, trgC, curNode.time + 1 } );
                    board[trgR][trgC] = VISITED;
                }
            }
        }
        
        if ( curQ->empty() == true ){
            queue<Node>* tmp = curQ;
            curQ = nextQ;
            nextQ = tmp;
        }
    }

    cout << estimated_time;

    // avoid mem leaks
    delete curQ;
    delete nextQ;

    return 0;
}