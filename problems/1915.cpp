/* smsh0722
 * 1915
 * 가장 큰 정사각형
 * */
#include <iostream>
using namespace std;

int findMin( int** dp, int r, int c );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int n, m;
    cin >> n >> m;
    int max = 0;

    char** map;
    int** dp;
    
    // Construct
    map = new char*[n];
    dp = new int*[n];
    for ( int r = 0; r < n; r++ ){
        map[r] = new char[m];
        dp[r] = new int[m];
        for ( int c = 0; c < m; c++ ){
            cin >> map[r][c];
            dp[r][c] = map[r][c] == '0' ? 0 : 1;
            max = max < dp[r][c] ? dp[r][c] : max;
        }
    }

    // Solve
    for ( int r = n - 2; r >= 0; r-- ){
        for ( int c = m - 2; c >= 0; c-- ){
            if ( map[r][c] == '0' ){
                dp[r][c] = 0;
                continue;
            }
            dp[r][c] = findMin( dp, r, c ) + 1;

            max = max < dp[r][c] ? dp[r][c] : max;
        }
    }

    // Debug
    /*
    {
        cout << "\n";
        for ( int i = 0; i < n; i++ ){
            for ( int j = 0; j < m; j++ ){
                cout << dp[i][j] << " ";
            } cout << "\n";
        }
    }
    */
   
    cout << max * max << "\n";

    return 0;
}

int findMin( int** dp, int r, int c )
{
    int min = dp[r+1][c];
    min = min > dp[r][c+1] ? dp[r][c+1] : min;
    min = min > dp[r+1][c+1] ? dp[r+1][c+1] : min;

    return min;
}