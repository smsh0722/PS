#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const 
    {
        return {r+other.r, c+other.c};
    };
};
struct QSearch{
    Vec2 pos;
    int dist;
};

const Vec2 UP = {-1,0};
const Vec2 DOWN = {1,0};
const Vec2 LEFT = {0,-1};
const Vec2 RIGHT = {0,1};
const vector<Vec2> MOVES = { LEFT, UP, RIGHT};
const int MAX_ARCHERS = 3;

// num of row
int N; 
// num of col
int M;
// num of range
int D;

int ans;
vector<vector<bool>> originalWorld;
vector<vector<bool>> world;
vector<Vec2> archers(MAX_ARCHERS);

inline void PrintWorld()
{
    cout << "------------------------------\n";
    for( int r = 0; r < N; r++ ){
        for ( int c= 0; c< M; c++ ){
            cout << world[r][c] << " ";
        } cout << endl;
    }
}
inline bool FindTarget( const Vec2& pos, Vec2& rst )
{
    queue<QSearch> q;
    vector<vector<bool>> visited(N, vector<bool>(M, false));

    q.push( {pos, 0});
    while ( q.empty() == false ){
        QSearch front = q.front();
        q.pop();

        for ( size_t i = 0; i < MOVES.size(); i++){
            Vec2 next = front.pos + MOVES[i];
            // Check out of range
            if ( next.r < 0 || next.r >= N || next.c < 0 || next.c >= M )
                continue;
            // Check already visited
            if ( visited[next.r][next.c] == true )
                continue;
            // check Is There enemy
            if ( world[next.r][next.c] == true ){
                rst = next;
                return true;
            }

            visited[next.r][next.c] = true;
            if ( front.dist + 1 < D )
                q.push({next, front.dist+1});
        }        
    }

    return false;
}
inline void SimulGame()
{   
    // printf("a[0](%d, %d), a[1](%d, %d), a[2](%d, %d)\n", archers[0].r, archers[0].c, archers[1].r, archers[1].c, archers[2].r, archers[2].c);
    int localAns= 0;
    world = originalWorld;
    for ( int turn = 0; turn < N; turn++ ){
        // 잡기
        queue<Vec2> trgs;
        for ( int i = 0; i < MAX_ARCHERS; i++ ){
            Vec2 trg = {0, 0};
            if ( FindTarget(archers[i], trg) == false )
                continue;
            trgs.push(trg);
        }
        while (trgs.empty() == false ){
            Vec2 trg = trgs.front();
            trgs.pop();
            if( world[trg.r][trg.c] == true ){
                localAns++;
                world[trg.r][trg.c] = false;
            }
        }

        // PrintWorld(); //Debug
        // printf("sum: %d\n", localAns);

        // 내려오기
        for ( int r = N-1; r >= 0; r-- ){
            for ( int c = 0; c < M; c++ ){
                if ( r + 1 < N && world[r][c] == true){
                    world[r+1][c] = world[r][c];
                }
                world[r][c] = false;
            }
        }
        // PrintWorld(); //Debug
    }
    // printf("^^^^^^^^localAns: %d^^^^^^^^^^\n", localAns);
    ans = ans < localAns ? localAns : ans;
}
void SetArcherPos( int count, int s )
{
    if ( count == 3 ){
        SimulGame();
        return; 
    }

    for ( int i = s; i < M; i++ ){
        archers[count] = {N, i};

        SetArcherPos(count+1, i+1);
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> D;
    originalWorld.resize(N, vector<bool>(M, false));
    world.resize(N, vector<bool>(M,false));
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            int val;
            cin >> val;
            if ( val == 1 )
                originalWorld[r][c] = true;
        }
    }

    SetArcherPos(0, 0);

    cout << ans;

    return 0;
}