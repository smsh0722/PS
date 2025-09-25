#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

const int MAX_NUM_PLAYERS = 26;

struct Vec2 {
    int r, c;
    Vec2 operator+( const Vec2& other ) const 
    {
        return {r+other.r, c+other.c};
    }
};
const Vec2 MOVES[4] = {
    {-1,0},
    {1,0},
    {0,-1},
    {0,1}
};

struct QNode {
    int w;
    Vec2 u;
};


// size of MxN world
int M, N;
// # of players [1,26]
int P; 

vector<int> players( MAX_NUM_PLAYERS, -1 );
vector<int> dpsOfPlayers( MAX_NUM_PLAYERS, 0 );
vector<int> bParticipated( MAX_NUM_PLAYERS, false );

vector<vector<char>> world;

Vec2 monsterPos;
int monsterHP;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Input
    cin >> M >> N >> P;
        // 맵 데이터
    world.resize(M, vector<char>(N, '.') );
    for ( int r = 0; r < M; r++ ){
        string line;
        cin >> line;
        for ( int c = 0; c < N; c++ ){
            world[r][c] = line[c];
            if ( line[c] == 'B' )
                monsterPos = Vec2{r, c};
        }
    }
        // 플레이어 dps
    for ( int i = 0; i < P; i++ ){
        char p;
        int dps;
        cin >> p >> dps;
        dpsOfPlayers[p-'a'] = dps;
    }
        // 몬스터 데이터
    cin >> monsterHP;
    
    // BFS monster to players: 각 플레이어 최단 경로 구하기.
    {
        queue<QNode> q;
        vector<vector<bool>> visited(M, vector<bool>(N, false) );

        q.push( QNode{0, monsterPos} );
        visited[monsterPos.r][monsterPos.c] = true;
        while (q.empty() == false ){
            QNode front = q.front();
            q.pop();

            for ( int mi = 0; mi < 4; mi++ ){
                Vec2 adjNode = front.u + MOVES[mi];
                if ( adjNode.r < 0 || adjNode.r >= M || adjNode.c < 0 || adjNode.c >= N )
                    continue;
                if ( visited[adjNode.r][adjNode.c] == true )
                    continue;

                char nodeData = world[adjNode.r][adjNode.c];
                if ( nodeData == 'X' )
                    continue;
                else {
                    QNode next = { front.w + 1, adjNode };
                    q.push(next);
                    visited[adjNode.r][adjNode.c] = true;
                    if ( 'a' <= nodeData && nodeData <= 'z' ){
                        players[nodeData-'a'] = next.w;
                    }
                }
            }
        }
    }

    // Loop game
    while ( monsterHP > 0 ){
        // 1. 보스 공격
        for ( int pi = 0; pi < MAX_NUM_PLAYERS; pi++ ){
            if ( players[pi] == 0 ){
                monsterHP -= dpsOfPlayers[pi];
                bParticipated[pi] = true;
            }
        }
        // 2. 이동
        for ( int pi = 0; pi < MAX_NUM_PLAYERS; pi++ ){
            if ( players[pi] > 0 ){
                players[pi]--;
            }
        }
    }

    // Answer
    int sum = 0;
    for ( int pi = 0; pi < MAX_NUM_PLAYERS; pi++ )
        sum += int(bParticipated[pi]);
    
    cout << sum;

    return 0;
}