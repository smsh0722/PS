#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const
    {
        return {r+other.r, c+other.c};
    }
};
struct BFS{
    int count;
    Vec2 pos;
};

const Vec2 MOVES[4] = 
{
    {-1,0},
    {1,0},
    {0,-1},
    {0,1}
};

const int INF = INT32_MAX;

// NxN world
int N;

vector<vector<bool>> world;
// dist[r][c] = # of change
vector<vector<int>> dist;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    world.resize(N, vector<bool>(N, true) );
    for ( int r = 0; r < N; r++ ){
        string s;
        cin >> s;
        for ( int c = 0; c < N; c++ ){
            world[r][c] = s[c] == '1';
        }
    }

    queue<BFS> bfs;
    dist.resize(N, vector<int>(N, INF) );
    bfs.push({ 0, 0, 0});
    dist[0][0] = 0;
    while ( bfs.empty() == false ){
        BFS cur = bfs.front();
        bfs.pop();

        if ( dist[cur.pos.r][cur.pos.c] < cur.count )
            continue;

        for ( auto move: MOVES ){
            Vec2 next = cur.pos + move;
            if ( next.r < 0 || next.r >= N || next.c < 0 || next.c >= N )
                continue;

            int nextCount = cur.count;
            if ( world[next.r][next.c] == false ){
                nextCount++;
            }

            if ( dist[next.r][next.c] > nextCount ){
                bfs.push({nextCount, next});
                dist[next.r][next.c] = nextCount;
            }         
        }
    }
    
    cout << dist[N-1][N-1];

    return 0;
}