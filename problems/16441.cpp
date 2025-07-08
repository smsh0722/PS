#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const {
        return Vec2{ r + other.r, c + other.c};
    }
    bool operator!=( const Vec2& other) const {
        return ((r!=other.r) || (c != other.c));
    }
};

int N, M; // NxM world

vector<vector<char>> world;
vector<Vec2> wolves;
vector<vector<bool>> visited;

inline void  GetNextList( vector<Vec2>& nextList, const Vec2& p);
inline void MoveWolf( vector<Vec2>& nextList, const Vec2& velocity, const Vec2& p);
void dfs( const Vec2& wolf );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    world.resize(N, vector<char>(M) ); // NOTE: resize 기본 construct처럼 사용
    visited.resize(N, vector<bool>(M, false ));
    for ( int r = 0; r < N; r++ ){
        string s;
        cin >> s;
        for ( int c = 0; c < M; c++ ){
            world[r][c] = s.at(c);
            if ( world[r][c] == 'W' ){
                    wolves.push_back(Vec2{r,c});
            }
        }
    }

    for ( size_t w = 0; w < wolves.size(); w++ ){
        Vec2 wolf = wolves[w];
        dfs(wolf);
    }

    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            if ( world[r][c] != '.' )
                cout << world[r][c];
            else {
                if( visited[r][c] == false )
                    cout << 'P';
                else 
                    cout << '.';
            }
        }
        cout << "\n";
    }
    return 0;
}

inline void GetNextList( vector<Vec2>& nextList, const Vec2& p)
{
    // left;
    Vec2 velocity = Vec2{0,-1};
    MoveWolf(nextList, velocity, p );
    // right
    velocity = Vec2{0,1};
    MoveWolf(nextList, velocity, p);
    // up
    velocity = Vec2{-1,0};
    MoveWolf(nextList, velocity, p);
    // down
    velocity = Vec2{1,0};
    MoveWolf(nextList, velocity, p);
}

inline void MoveWolf( vector<Vec2>& nextList, const Vec2& velocity, const Vec2& p)
{
    Vec2 prevP = p;
    while ( true ){
        Vec2 newP = prevP + velocity;
        
        if ( newP.r < 0 || newP.r >= N || newP.c < 0 || newP.c >= M )
            break;

        if ( world[newP.r][newP.c] == '#' )
            break;
        else if ( world[newP.r][newP.c] == '.' ){
            prevP = newP;
            break;
        } 
        else { // world == '+'
            prevP = newP;
        }
    }

    if ( p != prevP ){
        nextList.push_back(prevP);
    }
}

void dfs( const Vec2& wolf )
{
    visited[wolf.r][wolf.c] = true;

    vector<Vec2> nextList;
    GetNextList( nextList, wolf );
    for ( size_t i = 0; i < nextList.size(); i++ ){
        Vec2 next = nextList[i];
        
        if ( visited[next.r][next.c] == true )
            continue;
        dfs(next);
    }
}