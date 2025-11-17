#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int NUM_OF_FRONT_CHAR = 5;

// # of words
int N;
vector<string> words;

// memo[front char][used bits] = # of cases
vector<vector<int>> memo;

inline int GetIndexOfChar( char c )
{
    switch (c)
    {   
    case 'A':
        return 0;
    case 'E':
        return 1;
    case 'I':
        return 2;
    case 'O':
        return 3;
    case 'U':
        return 4;
    default:
        return -1;
    }
}

int DFS( int front, int used )
{
    if ( memo[front][used] != -1 )
        return memo[front][used];

    int rst = 0;
    for ( int i = 0; i < N; i++ ){
        const string& word = words[i];
        int wordBits = 1<<i;
        if ( used & wordBits )
            continue;
        if ( GetIndexOfChar(word.front() ) != front )
            continue;
        
        rst = max( rst, DFS( GetIndexOfChar(word.back()), used|wordBits) + int(word.length()) );
    }

    return (memo[front][used] = rst );
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    words.resize(N);
    for ( int ni = 0; ni < N; ni++){
        cin >> words[ni];
    }

    memo.resize(NUM_OF_FRONT_CHAR, vector<int>(1<<N, -1) );
    for ( int i = 0; i < NUM_OF_FRONT_CHAR; i++ )
        DFS(i, 0);

    int ans = 0;
    for ( int i = 0; i < NUM_OF_FRONT_CHAR; i++ )
        ans = max( ans, memo[i][0] );
    cout << ans;

    return 0;
}