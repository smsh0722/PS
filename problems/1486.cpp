/*
0   4   8   12  16
1   2   3   4   20
2   3   4   5   24
3   4   5   32  28
4   5   6   36  50
5   6   7   50  100

UP to 100
1)
16*9+196+2500 = 2840
2)
1*7+43^2+2500 = 4356
DOWN
1)
11
2)
9

=> 입산, 하산 경로 다를 수 있음

MAX_V = 2500
MAX_E = 10000

입산)
(0,0)에서 Dijkstra = O(ElogV)
하산)
(r,c)에서 Dijkstra = O(ElogV)*O(NM)

*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+(const Vec2& other ) const 
    {
        return {r + other.r, c + other.c};
    }
};
struct Dijkstra {
    int time;
    Vec2 pos;
};
struct DijkstraCompare{
    bool operator() (const Dijkstra& a, const Dijkstra& b )
    {
        return a.time > b.time; // Desc by time
    }
};

const Vec2 MOVES[4] = {
    {-1,0}, {1, 0},
    {0, -1}, {0, 1}
};

const int INF = INT32_MAX;

// NxM mountain
int N, M;
// Diff limit
int T;
// Time limit
int D;

vector<vector<int>> mountain;
vector<vector<int>> upTimes;

void CalculateShortestPath( vector<vector<int>>& shortestPath, const Vec2 sPos )
{
    priority_queue<Dijkstra, vector<Dijkstra>, DijkstraCompare> pq;
    pq.push({0, sPos} );
    shortestPath[sPos.r][sPos.c] = 0;
    while ( pq.empty() == false ){
        Dijkstra cur = pq.top();
        pq.pop();

        if( shortestPath[cur.pos.r][cur.pos.c] < cur.time )
            continue;
        
        for ( const auto& move: MOVES ){
            Vec2 nextPos = cur.pos + move;
            if ( nextPos.r < 0 || nextPos.r >= N || nextPos.c < 0 || nextPos.c >= M )
                continue;

            int hDiff = mountain[nextPos.r][nextPos.c] - mountain[cur.pos.r][cur.pos.c];
            if ( abs(hDiff) > T )
                continue;

            int nextTime = hDiff <= 0 ? 1 : hDiff*hDiff;
            nextTime += cur.time;
            if ( nextTime < shortestPath[nextPos.r][nextPos.c] ){
                pq.push({nextTime, nextPos});
                shortestPath[nextPos.r][nextPos.c] = nextTime;
            }
        }
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> T >> D;
    mountain.resize(N, vector<int>(M));
    for ( int r = 0 ; r < N; r++ ){
        string s;
        cin >> s;
        for ( int c = 0; c < M; c++ ){
            char hChar = s[c];
            if ( hChar >= 'a' )
                mountain[r][c] = hChar - 'a' + 26;
            else 
                mountain[r][c] = hChar - 'A';
        }
    }

    // Calculate UPhill
    upTimes.resize(N, vector<int>(M, INF) );
    CalculateShortestPath( upTimes, Vec2{0,0} );
    
    // Find ans
    int ans = 0;
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            int upTime = upTimes[r][c];
            int downTime = INF;
            
            // Caculate Downhill
            vector<vector<int>> downTimes(N, vector<int>(M, INF));
            CalculateShortestPath( downTimes, Vec2{r,c} );
            
            downTime = downTimes[0][0];

            if ( downTime == INF || upTime + downTime > D )
                continue;

            ans = max(ans, mountain[r][c] );
        }
    }

    cout << ans;

    return 0;
}