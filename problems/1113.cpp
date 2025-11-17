#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const 
    {
        return {r+other.r, c + other.c};
    }
};

const Vec2 MOVES[4] = 
{
    {0,1},
    {0,-1},
    {-1,0},
    {1,0}
};

const int MAX_POOL_LEVEL = 9;

// NxM pool
int N, M;
/* ex) 2x2 pool
0000
0130
0230
0000
*/
vector<vector<int>> pool;
vector<vector<Vec2>> levels(MAX_POOL_LEVEL+1);

int ans = 0;

void FindMinMax( const Vec2& sPos, int& minH, int& higherH )
{
    vector<vector<bool>> visited(N+2, vector<bool>(M+2, false));
    queue<Vec2> bfs;

    bfs.push(sPos);
    visited[sPos.r][sPos.c] = true;
    while ( bfs.empty() == false ){
        Vec2 cur = bfs.front();
        bfs.pop();

        for ( auto move : MOVES ){
            Vec2 next = cur + move;

            if ( visited[next.r][next.c] == true )
                continue;
            visited[next.r][next.c] = true;

            int nextH = pool[next.r][next.c];
            if ( nextH > pool[sPos.r][sPos.c] ){
                higherH = min(higherH, nextH);
            }
            else if ( nextH == pool[sPos.r][sPos.c] ){
                bfs.push(next);
            }
            else {
                minH = min( minH, nextH );
                break;
            }
        }

        if ( minH < pool[sPos.r][sPos.c] )
            break;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    pool.resize(N+2, vector<int>(M+2, 0));
    for ( int r = 1; r <= N; r++ ){
        string s;
        cin >> s;
        for ( int c = 1; c <= M; c++ ){
            pool[r][c] = s[c-1] - '0';
            levels[pool[r][c]].push_back({r,c});
        }
    }


    for ( int level = 1; level <= MAX_POOL_LEVEL; level++ ){
        for ( auto cur : levels[level] ){
            int minH = pool[cur.r][cur.c];
            int higherH = INT32_MAX;

            FindMinMax( cur, minH, higherH);
            // cout << cur.r << ", " << cur.c << " minH: " << minH << " higherH: " << higherH <<endl;// DEBUG
            if ( pool[cur.r][cur.c] == minH && pool[cur.r][cur.c] < higherH){
                ans += higherH - pool[cur.r][cur.c];
                pool[cur.r][cur.c] = higherH;
                levels[higherH].push_back(cur);
            }
        }
    }

    cout << ans;

    return 0;
}