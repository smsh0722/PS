/* NOTE:
처음엔 단순 BFS로 생각하여 풀었다.

그러나 시간 초과가 됐다.
잘 생각해보면 멀리가든 돌아가든 일단 벽을 가장 적게 부수는 경우를 먼저 확인해야한다.
따라서 우선순위 큐를 사용해야 한다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const 
    {
        return {r + other.r, c + other.c};
    }
};

struct QData{
    int count;
    Vec2 pos;
};
struct QDataCompareAscByCount{
    bool operator()( const QData& a, const QData& b )
    {
        return a.count > b.count;
    }
};

const Vec2 MOVES[4] = {
    {0, -1},
    {0, 1},
    {-1, 0},
    {1, 0}
};

// NxM world
int N; int M;

vector<vector<bool>> world;
vector<vector<int>> dijkstra;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> M >> N;
    
    world.resize(N, vector<bool>(M));
    for ( int r = 0; r < N; r++ ){
        string line;
        cin >> line;
        for ( int c = 0; c < M; c++ ){
            if ( line[c] == '1' )
                world[r][c] = true;
            else 
                world[r][c] = false;
        }
    }

    dijkstra.resize(N, vector<int>(M, INT32_MAX));
    priority_queue<QData, vector<QData>, QDataCompareAscByCount> q;
    q.push({0, 0, 0});
    dijkstra[0][0] = 0;
    while ( q.empty() == false ){
        QData cur = q.top();
        q.pop();

        if( dijkstra[cur.pos.r][cur.pos.c] < cur.count )
            continue;

        if ( cur.pos.r == N -1 && cur.pos.c == M - 1 ){
            cout << cur.count;
            return 0;
        }

        for ( auto move : MOVES ){
            Vec2 next = cur.pos + move;

            if ( next.r < 0 || next.r >= N || next.c < 0 || next.c >= M )
                continue;

            if ( world[next.r][next.c] == true ){
                if ( cur.count >= N*M )
                    continue;

                if ( dijkstra[next.r][next.c] > cur.count + 1){
                    q.push({cur.count+1, next});
                    dijkstra[next.r][next.c] = cur.count+1;
                }
            }
            else {
                if ( dijkstra[next.r][next.c] > cur.count ){
                    q.push({cur.count, next});
                    dijkstra[next.r][next.c] = cur.count;
                }
            }
        }
    }

    return 0;
}
