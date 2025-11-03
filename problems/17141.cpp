#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Vec2{
    int r, c;
    Vec2( int r, int c ):r(r), c(c){}
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

const int INF = INT32_MAX;
int ans = INF;

// NxN Lab
int N;
// # of trigger
int M;

vector<vector<int>> originalLab;
int targetEmptyNum = 0;
vector<Vec2> viruses;

void DoSimulation( const vector<int>& startings )
{
    vector<vector<int>> lab( N, vector<int>(N, -1) );
    int leftEmptyNum = targetEmptyNum;
    queue<Vec2> q;
    for ( auto i: startings ){
        Vec2 virus = viruses[i];
        q.push( virus );
        lab[virus.r][virus.c] = 0;
    }

    int rst = 0;
    while ( q.empty() == false ){
        Vec2 cur = q.front();
        q.pop();

        rst = max( lab[cur.r][cur.c], rst );

        if ( originalLab[cur.r][cur.c] != 1 )
            leftEmptyNum--;

        for ( Vec2 move : MOVES ){
            Vec2 next = cur + move;
            // Out of range
            if ( next.r < 0 || next.r >= N || next.c < 0 || next.c >= N )
                continue;
            // Visited
            if ( lab[next.r][next.c] != -1 )
                continue;
            
            if ( originalLab[next.r][next.c] != 1 ){
                lab[next.r][next.c] = lab[cur.r][cur.c] + 1;
                q.push(next);
            }
        }
    }

    // cout << leftEmptyNum << endl; // DEBUG
    if ( leftEmptyNum == 0 )
        ans = min(ans, rst);
}

void TryEachCaseRecursive( int count, int prev, vector<int>& startings )
{
    if ( count == M ){
        DoSimulation( startings );
    }
    
    for ( int i = prev + 1; i < int(viruses.size()); i++ ){
        startings.push_back(i);
        TryEachCaseRecursive( count + 1, i, startings );
        startings.pop_back();
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    originalLab.resize(N, vector<int>(N,0));
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < N; c++ ){
            cin >> originalLab[r][c];

            targetEmptyNum += originalLab[r][c] != 1 ? 1 : 0;

            if ( originalLab[r][c] == 2 ){
                viruses.push_back( Vec2( r, c ) );
            }
        }
    }

    vector<int> startings;
    TryEachCaseRecursive( 0, -1, startings );

    if ( ans == INF)
        cout << -1;
    else 
        cout << ans;

    return 0;
}