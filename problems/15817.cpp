#include <iostream>
#include <vector>
using namespace std;

const int MAX_PIPES_NUM = 100;
const int MAX_TARGET_LENGTH = 10000;

struct Pipe{
    int len;
    int count;
};

// # of pipes
int N;
// Target Length
int x;

vector<Pipe> pipes;

// memo[pipe idx][left length] = num of cases
vector<vector<int>> memo( MAX_PIPES_NUM, vector<int>(MAX_TARGET_LENGTH, -1) );

int SolveRecursive( int pi, int leftLen )
{
    if ( memo[pi][leftLen] != -1 )
        return memo[pi][leftLen];
    
    int rst = 0;
    int nextPi = pi +1;
    for ( int i = 0; i <= pipes[pi].count; i++ ){
        int nextLeftLen = leftLen - pipes[pi].len * i;
        if ( nextLeftLen > 0 && nextPi < N )
            rst += SolveRecursive( nextPi, nextLeftLen );
        if ( nextLeftLen == 0 )
            rst++;
    }

    return memo[pi][leftLen] = rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> x;
    pipes.resize(N);
    for ( int pi = 0; pi < N; pi++ ){
        cin >> pipes[pi].len >> pipes[pi].count;
    }

    cout << SolveRecursive( 0, x );

    return 0;
}