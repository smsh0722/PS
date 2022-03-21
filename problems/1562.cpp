/* smsh0722
 * 1562
 * 계단 수
 * */
#include <iostream>
#include <cstring>
using namespace std;

int main( void )
{
    int N; 
    cin >> N;

    /* dp[a][b][c]
     * a = N, 0~99
     * b = num, {0, 1, 2, ..., 9}
     * c = bitIdx, 00 0000 0000(0) ~ 11 1111 1111(1023)
     * */
    int64_t* dp[100][10];
    for ( int i = 0; i < 100; i++ ){
        for ( int j = 0; j < 10; j++ ){
            dp[i][j] = new int64_t[1024];
            memset( dp[i][j], 0, sizeof(int64_t)*1024 );
        }
    }

    // DP
    for ( int i = 1; i < 10; i++ )
        dp[0][i][1<<i] = 1;
    
    for ( int n = 1; n < N; n++ ){
        for ( int j = 0; j < 10; j++ ){
            int up = j + 1;
            int down = j - 1;

            if ( up >= 0 && up <= 9 ){
                for ( int k = 0; k < 1024; k++ ){
                    dp[n][j][k|(1<<j)] += dp[n-1][up][k];
                    dp[n][j][k|(1<<j)] %= 1000000000;
                }
            }

            if ( down >= 0 && down <= 9){
                for ( int k = 0; k < 1024; k++ ){
                    dp[n][j][k|(1<<j)] += dp[n-1][down][k];
                    dp[n][j][k|(1<<j)] %= 1000000000;
                }
            }
        }
    }

    int64_t count = 0;

    for ( int i = 0; i < 10; i++ ){
        count += dp[N-1][i][1023];
        count %= 1000000000;
    }
    
    cout << count;
    return 0;
}