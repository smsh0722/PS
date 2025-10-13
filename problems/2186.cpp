#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const 
    {
        return {r+other.r, c+other.c };
    }
    Vec2 operator*(const int l ) const 
    {
        return {r*l, c*l};
    }
};

const Vec2 MOVES[4] = {
    {-1,0},
    {1,0},
    {0,-1},
    {0,1}
};

// NxM board
int N, M;
// Max move dist at each step
int K;

string trgWord = "";
int trgWordLen = 0;
vector<string> board;

// dpMemp[r][c][leftLen] = Possible Count;
vector<vector<vector<int>>> dpMemo;

int DFS( Vec2 pos, int leftLen )
{
    if ( leftLen == 0 )
        return 1;

    if ( dpMemo[pos.r][pos.c][leftLen] != -1 )
        return dpMemo[pos.r][pos.c][leftLen];

    int count = 0;
    int nextIdx = trgWordLen - leftLen;
    for ( auto move : MOVES ){
        for ( int k = 1; k <= K; k++ ){
            Vec2 next = pos + move*k;
            if ( next.r < 0 || next.r >= N || next.c < 0 || next.c > M )
                continue;
            
            // Compare char
            if ( board[next.r][next.c] != trgWord[nextIdx] )
                continue;
            
            count += DFS( next, leftLen - 1);
        }
    }

    return (dpMemo[pos.r][pos.c][leftLen] = count);
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;

    board.resize(N);
    for ( int r = 0; r < N; r++ )
        cin >> board[r];
        
    cin >> trgWord;
    trgWordLen = int(trgWord.length() );

    int ans = 0;
    dpMemo.resize(N, vector<vector<int>>(
            M, vector<int>( 
                trgWordLen + 1, -1 
            )
        )
    );
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            if ( board[r][c] != trgWord[0] )
                continue;
            ans += DFS( {r,c}, trgWordLen - 1  );
        }
    }

    cout << ans;

    return 0;
}