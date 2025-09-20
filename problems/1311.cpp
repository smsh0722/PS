/* NOTE:
아무 생각 없이 DP 이차원으로 잡았음
그러나 그냥 bits field만 잇으면 됨.
*/
#include <iostream>
#include <vector>
using namespace std;

int N;

// D[people idx][job idx]
// people: [0,N-1], job[0,N-1]
vector<vector<int>> D;

// dpMemo[mask];
vector<int> dpMemo;

int SolveRecursive( int visitedMask, int left )
{
    if ( dpMemo[visitedMask] != -1 )
        return dpMemo[visitedMask];
    if ( left == 0 )
        return 0;

    int rst = INT32_MAX;
    for ( int i = 0; i < N; i++ ){
        if ( visitedMask & (1<<i) )
            continue;
        rst = min(rst, SolveRecursive(visitedMask|(1<<i), left-1) + D[N-left][i] );
    }

    return dpMemo[visitedMask] = rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);

    cin >> N;
    D.resize(N, vector<int>(N) );
    for ( int i = 0; i < N; i++ ){
        for( int j = 0; j < N; j++ )
            cin >> D[i][j];
    }

    // Fill dpMemo
    dpMemo.resize((1<<N), -1);

    cout << SolveRecursive( 0, N );

    return 0;
}

// #include <iostream>
// #include <vector>
// using namespace std;

// int N;

// // D[people idx][job idx]
// // people: [0,N-1], job[0,N-1]
// vector<vector<int>> D;

// // dpMemo[mask][left];
// vector<vector<int>> dpMemo;

// int SolveRecursive( int visitedMask, int left )
// {
//     if ( dpMemo[visitedMask][left] != -1 )
//         return dpMemo[visitedMask][left];
//     if ( left == 0 )
//         return 0;

//     int rst = INT32_MAX;
//     for ( int i = 0; i < N; i++ ){
//         if ( visitedMask & (1<<i) )
//             continue;
//         rst = min(rst, SolveRecursive(visitedMask|(1<<i), left-1) + D[N-left][i] );
//     }

//     return dpMemo[visitedMask][left] = rst;
// }

// int main( void )
// {
//     ios_base::sync_with_stdio(false);cin.tie(NULL);

//     cin >> N;
//     D.resize(N, vector<int>(N) );
//     for ( int i = 0; i < N; i++ ){
//         for( int j = 0; j < N; j++ )
//             cin >> D[i][j];
//     }

//     // Fill dpMemo
//     dpMemo.resize((1<<N), vector<int>(N+1, -1 ) );

//     cout << SolveRecursive( 0, N );

//     return 0;
// }