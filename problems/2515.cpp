/* NOTE: 실패
dp를 include 0 과 1로만 하면 예외 생김.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Paint {
    int h, c;
};

// # of paints
int N;
// size of Min
int S;

vector<Paint> paints;

// dpMemo[paint#][0(not include) or 1 inclue] = max price from paint# to end paint
vector<vector<int>> dpMemo;

bool ComaprePaintAscByH( const Paint& a, const Paint& b )
{
    if ( a.h == b.h )
        return a.c > b.c;
    return a.h < b.h;
}

int DFS( int pi, int lastH )
{
    if ( pi == N )
        return 0;

    bool bCanInclude = ((paints[pi].h - lastH) >= S);
    if ( dpMemo[pi][bCanInclude] != -1 )
        return dpMemo[pi][bCanInclude];

    int rst = 0;
        // case1: cur 건너뛰기    
    rst = DFS(pi+1, lastH );
        // case2: cur 포함
    if ( bCanInclude ){
        rst = max( rst,
            DFS(pi+1, paints[pi].h ) + paints[pi].c
        );
    }

    return dpMemo[pi][bCanInclude] = rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Input
    cin >> N >> S;
        // Get Paints datas
    paints.resize(N);
    for ( int pi = 0; pi < N; pi++ ){
        cin >> paints[pi].h >> paints[pi].c;
    }
    sort( paints.begin(), paints.end(), ComaprePaintAscByH);

    // Build DP Table
    dpMemo.resize(N);
    for ( int i = 0; i < N; i++ )
        dpMemo[i].resize(2, -1);
    DFS(0, 0);

    cout << max(dpMemo[0][0], dpMemo[0][1] );

    return 0;
}