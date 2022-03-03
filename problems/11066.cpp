/* by smsh0722
 * 11066
 * 파일 합치기
 * */
#include <iostream>
using namespace std;

const int INF = 5000001; // 5,000,001

int dp[501][501];
int segSum[501][501];

void solve();

int main( void )
{
    ios_base::sync_with_stdio(false); cout.tie(NULL); cin.tie(NULL);

    for ( int i = 0; i <= 500; i++ ){
        dp[0][i] = 0; dp[i][0] = 0;
        dp[i][i] = 0;
        segSum[i][0] = 0; segSum[0][i] = 0;
    }

    int T; cin >> T;

    for ( int i = 0; i < T; i++ )
        solve();
}

void solve()
{
    int n; cin >> n;

    int* chapters = new int[n+1];
    for ( int i = 1; i <= n; i++ ){
        cin >> chapters[i];
        segSum[1][i] = segSum[1][i-1] + chapters[i];
    }
    // Construct segSum
    for ( int i = 2; i <= n; i++ ){
        for ( int j = i; j <= n; j++ ){
            segSum[i][j] = segSum[1][j] - segSum[1][i-1];
        }
    }
    // Construct DP
    for ( int i = n; i >= 1; i-- ){
        for ( int j = i+1; j <= n; j++ ){
            dp[i][j] = INF;
            for ( int mid = i; mid <= j; mid++ ){
                int tmp = dp[i][mid] + dp[mid+1][j] + segSum[i][j];
                dp[i][j] = dp[i][j] > tmp ? tmp : dp[i][j];
            }
        }
    }

    cout << dp[1][n] << "\n";
}