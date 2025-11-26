#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_VISIT = (1<<16)-1;

// NxM borad
int N, M;

vector<vector<int>> board;

vector<int> memo(MAX_VISIT+1, -1);

inline int GetIdx( int r, int c )
{
    return (r*M+c);
};

int Solve( int visited )
{
    if( memo[visited] != -1 )
        return memo[visited];

    int next = 0;
    for ( ; next < N*M; next++ ){
        if ( ( visited&(1<<next) )== 0)
            break;
    }

    if ( next >= N*M )
        return 0;

    int rst = 0;

    const int r = next / M;
    const int c = next % M;
    // 오른쪽으로
    {
        int num = 0;
        int nextVisited = visited;
        for ( int ce = c; ce < M; ce++ ){
            if ( nextVisited & (1<<GetIdx(r,ce)) )
                break;
            num = num * 10 + board[r][ce];
            nextVisited = nextVisited | (1<<GetIdx(r,ce));
            int tmpRst = num + Solve( nextVisited );

            rst = max( rst, tmpRst );
        }
    }

    // 아래로
    {
        int num = 0;
        int nextVisited = visited;
        for ( int re = r; re < N; re++ ){
            num = num * 10 + board[re][c];
            nextVisited = nextVisited | (1<<GetIdx(re,c));
            int tmpRst = num + Solve( nextVisited );

            rst = max( rst, tmpRst );
        }
    }

    return memo[visited] = rst;
}

int main (void )
{
    ios_base::sync_with_stdio(false ); cin.tie(NULL);

    cin >> N >> M;

    board.resize(N, vector<int>(M));
    for ( int r = 0; r < N; r++ ){
        string s;
        cin >> s;

        for ( int c = 0; c < M; c++ ){
            board[r][c] = s[c]-'0';
        }
    }

    cout << Solve( 0 );

    return 0;
}