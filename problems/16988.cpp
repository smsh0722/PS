#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const 
    {
        return { r+ other.r, c + other.c };
    }
};

const Vec2 adjMoves[4] = {{-1,0}, {1,0}, {0,-1}, {0,1} };

int N, M;
vector<vector<int>> board;

void printBoard()
{
    for ( int r = 0; r < N; r++ ){
        for ( int  c = 0; c< M; c++ ){
            cout << board[r][c] << " ";
        } cout << endl;
    }
}

int HowManyKill()
{
    int count = 0;

    vector<vector<bool>> visited(N, vector<bool>( M, false ) );
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            if ( visited[r][c] == true )
                continue;

            // 흑돌 조사 시작
            if ( board[r][c] == 2 ){
                int localCount = 0;
                bool bIsAlive = false;
                
                // BFS
                queue<Vec2> q; // 흑돌
                q.push( {r,c} );
                visited[r][c] = true;
                while ( q.empty() == false ){
                    Vec2 Node = q.front();
                    q.pop();
                    localCount++;

                    
                    for ( int i = 0; i < 4; i++ ){
                        Vec2 adjNode = Node + adjMoves[i];
                        if ( adjNode.r < 0 || adjNode.r >= N || adjNode.c < 0 || adjNode.c >= M )
                            continue;
                        
                        if ( board[adjNode.r][adjNode.c] == 2 ){ // 인접 흑
                            if (visited[adjNode.r][adjNode.c] == false ){
                                q.push( adjNode );
                                visited[adjNode.r][adjNode.c] = true;
                            }
                        }
                        else if ( board[adjNode.r][adjNode.c] == 0 ){ // 인접 빈
                            bIsAlive = true;
                        }
                    }
                }

                if ( bIsAlive == false ){
                    count += localCount;
                }
            }
        }
    }

    return count;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    board.resize(N, vector<int>(M));
    for ( int r = 0; r < N; r++ ) {
        for ( int c = 0; c < M; c++ ){
            cin >> board[r][c];
        }
    }

    // 모든 칸 두어보기
    int ans = 0;
    for ( int i = 0; i < N*M; i++ ){
        for ( int j = i+1; j < N*M; j++ ){
            int ir = i / M;
            int ic = i % M;
            int jr = j / M;
            int jc = j % M;

            if ( board[ir][ic] == 0 && board[jr][jc] == 0){
                board[ir][ic] = 1;
                board[jr][jc] = 1;
                ans = max( ans, HowManyKill() );

                board[ir][ic] = 0;
                board[jr][jc] = 0;
            }
        }
    }

    cout << ans;
    return 0;
}