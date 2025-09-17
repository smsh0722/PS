#include <iostream>
#include <vector>
using namespace std;

// Size of Row
int M;
// Size of Col
int N;

inline int FindMax( vector<int>& v )
{
    size_t size = v.size();
    if ( size == 1 )
        return v[0];
    if ( size == 2 )
        return max(v[0], v[1] );
    if ( size == 3 )
        return max( v[0] + v[2], v[1] );

    // size >= 4
    vector<int> dp(size, 0);
    dp[0] = v[0];
    dp[1] = v[1];
    dp[2] = v[0] + v[2];
    for ( size_t i = 3; i < size; i++ ){
        dp[i] = max( dp[i-2], dp[i-3] ) + v[i];
    }   

    return max(dp[size-1], dp[size-2] );
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    while ( true ){
        cin >> M >> N;
        if ( M == 0 && N == 0 )
            break;

        vector<vector<int>> candyBox(M, vector<int>(N) );
        for ( int r = 0; r < M; r++ ) {
            for ( int c = 0; c < N; c++ ){
                cin >> candyBox[r][c];
            }
        }
        
        vector<int> maxInEachRow(M, 0);
        // 각 row의 최대 찾기
        for ( int r = 0; r < M; r++ ){
            maxInEachRow[r] = FindMax( candyBox[r] );
        }

        // 최대 row 조합 찾기
        cout << FindMax(maxInEachRow) << "\n";
    }

    return 0;
}