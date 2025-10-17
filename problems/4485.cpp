#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2 other ) const 
    {
        return {r+other.r, c+other.c};
    }
};

struct PQ{
    Vec2 node;
    int dist;
};
struct PQCompare{
    bool operator()( const PQ& a, const PQ& b )
    {
        return a.dist > b.dist;
    }
};

const Vec2 MOVES[4] = {
    {-1,0},
    {1,0},
    {0,-1},
    {0,1}
};
const int INF = INT32_MAX;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int problemCount = 0;
    while ( true ){
        problemCount++;
        int N;
        cin >> N;
        if ( N == 0 ) break;

        vector<vector<int>> world(N, vector<int>(N, 0) );
        for ( int r = 0; r < N; r++ ){
            for ( int c = 0; c < N; c++ ){
                cin >> world[r][c];
            }
        }

        vector<vector<int>> dijkstra(N, vector<int>(N, INF) );
        priority_queue<PQ, vector<PQ>, PQCompare> pq;
        pq.push({{0,0}, world[0][0] } );
        dijkstra[0][0] = world[0][0];
        while ( pq.empty() == false ){
            PQ top = pq.top();
            pq.pop();
            if ( dijkstra[top.node.r][top.node.c] < top.dist )
                continue;
            
            for ( int mi = 0; mi < 4; mi++ ){
                Vec2 next = top.node + MOVES[mi];
                if ( next.r < 0 || next.r >= N || next.c < 0 || next.c >= N )
                    continue;
                int newDist = world[next.r][next.c] + top.dist;
                if ( newDist < dijkstra[next.r][next.c] ){
                    pq.push({next, newDist});
                    dijkstra[next.r][next.c] = newDist;
                }
            }
        }

        cout << "Problem " << problemCount << ": " <<  dijkstra[N-1][N-1] << endl;
    }

    return 0;
}