/* smsh0722
 * 14502
 * 연구소
 * */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

int N, M;

struct Node{
    int r;
    int c;
};

/* Create all possible Cases
 * if (wallCount == 3), test a case
 * return max case
 * default parameter == {r, c, wallCount }
 * */
int bruteForce( int** lab, queue<Node>* virusQ, int emptyCount, int r = 0, int c = -1, int wallCount = 0 );
/* Test current test Case*/
int testCurCase( int** lab, queue<Node> virusQ, int emptyCount );
/* Delete 2-Dimensional int Array */
inline void delete2dInt( int** lab );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); 
    cin >> N >> M;
    
    /* Store virus cells for BFS */
    queue<Node> virusQ;

    /* Store # of Empty wall */
    int emptyCount = 0;

    /* Store current lab condition */
    int** lab = new int*[N];
    
    // Preprocess
    for ( int r = 0; r < N; r++ ){
        lab[r] = new int[M];

        // Input
        for ( int c = 0; c < M; c++ ){
            cin >> lab[r][c];

            if ( lab[r][c] == 0 )
                emptyCount++;
            else if ( lab[r][c] == 2 )
                virusQ.push( {r,c} );
        }
    }

    // Solve
    cout << bruteForce( lab, &virusQ, emptyCount );
    
    return 0;
}
int bruteForce( int** lab, queue<Node>* virusQ, int emptyCount, int r, int c, int wallCount )
{
    int max = 0;
    // Base Case
    if ( wallCount == 3 ){
        int** newLab = new int*[N];
        for ( int i = 0; i < N; i++ ){
            newLab[i] = new int[M];
            for ( int j = 0; j < M; j++ )
                newLab[i][j] = lab[i][j];
        }

        int rst = testCurCase( newLab, *virusQ, emptyCount );
        delete2dInt( newLab );

        return rst;
    }

    // Make Case recursively
    for ( int i = r; i < N; i++ ){
        for ( int j = c + 1; j < M; j++ ){
            if ( lab[i][j] == 0 ){
                lab[i][j] = 1;

                int rst = bruteForce( lab, virusQ, emptyCount - 1, i, j, wallCount + 1 );
                max = max < rst ? rst : max;
                
                lab[i][j] = 0; // reset
            }
        }
        /* i == r, j start from c + 1,
         * from i == r + 1, j start from 0
         * */
        c = -1; 
    }

    return max;
}
int testCurCase( int** lab, queue<Node> virusQ, int emptyCount )
{
    // Breadth First Search
    while( virusQ.empty() == false ){
        Node curNode = virusQ.front(); virusQ.pop();
        
        /* Adjacency Node */
        int adjNode[4][2];
        adjNode[0][0] = curNode.r - 1; adjNode[0][1] = curNode.c;
        adjNode[1][0] = curNode.r + 1; adjNode[1][1] = curNode.c;
        adjNode[2][0] = curNode.r;     adjNode[2][1] = curNode.c - 1;
        adjNode[3][0] = curNode.r;     adjNode[3][1] = curNode.c + 1;
        for ( int i = 0; i < 4; i++ ){
            int trgR = adjNode[i][0];
            int trgC = adjNode[i][1];
            if ( trgR < 0 || trgR >= N )
                continue;
            if ( trgC < 0 || trgC >= M )
                continue;
            if ( lab[trgR][trgC] != 0 )  
                continue;
            
            lab[trgR][trgC] = 2; // Spread
            emptyCount--;        // Decrease # of empty cell

            virusQ.push( {trgR, trgC} );
        }
    }

    return emptyCount;
}
inline void delete2dInt( int** lab )
{   
    for ( int r = 0; r < N; r++ )
        delete[] lab[r];
    delete[] lab;
}