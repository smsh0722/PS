#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Vec2{
    int x, y;
    Vec2 operator+( const Vec2& other ) const 
    {
        return {x+other.x, y+other.y};
    }
    bool operator==( const Vec2& other ) const 
    {
        return ( x==other.x)&&(y==other.y);
    }
};

struct QNode{
    int dist;
    int leftBreakCount;
    Vec2 pos;
};

const Vec2 MOVES[4] = {
    {1, 0},
    {-1,0},
    {0,1},
    {0,-1}
};

// size of NxM mat
int N, M;

// start
Vec2 H;
// end
Vec2 E;

vector<vector<int>> world;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    cin >> H.x >> H.y; 
    cin >> E.x >> E.y;
    world.resize(N, vector<int>(M));
    for ( int x = 0; x < N; x++ ){
        for ( int y = 0; y < M; y++ ){
            cin >> world[x][y];
        }
    }

    int ans = -1;
    {
        vector<vector<int>> visited(N, vector<int>(M, 0) );
        queue<QNode> q;

        H = H + Vec2{-1,-1};
        E = E + Vec2{-1,-1};

        q.push({0,1, H} );
        visited[H.x][H.y] = 2;
        while ( q.empty() == false && ans == -1){
            QNode f = q.front();
            q.pop();
            
            
            for ( int mi = 0; mi < 4; mi++ ){
                Vec2 nextPos = f.pos + MOVES[mi];
                if ( nextPos.x < 0 || nextPos.x >= N || nextPos.y < 0 || nextPos.y >= M )
                    continue;
                if ( visited[nextPos.x][nextPos.y] - f.leftBreakCount > 0 )
                    continue;
                
                if( E == nextPos ){
                    ans = f.dist + 1;
                    break;
                }
                
                if( world[nextPos.x][nextPos.y] == 0 ){
                    QNode newQNode = f;
                    newQNode.dist++;
                    newQNode.pos = nextPos;
                    q.push( newQNode );
                    visited[nextPos.x][nextPos.y] = 1 + f.leftBreakCount;
                }
                else if ( f.leftBreakCount > 0 ) {
                    QNode newQNode = f;
                    newQNode.dist++;
                    newQNode.leftBreakCount--;
                    newQNode.pos = nextPos;
                    q.push(newQNode);
                    visited[nextPos.x][nextPos.y] = 1;
                }
            }
        }
    }

    cout << ans;

    return 0;
}