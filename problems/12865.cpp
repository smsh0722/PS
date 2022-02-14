#include <iostream>
using namespace std;

const int MAXITEM = 100;
inline int max_ab( int a, int b )
{
    return a > b ? a : b;
}
int main( void )
{
    int N, K;
    int items[MAXITEM][2]; // w, v
    cin >> N >> K;
    for ( int i = 0; i < N; i++ )
        cin >> items[i][0] >> items[i][1];
    
    int dp[N+1][K+1];
    for ( int item_i = 0; item_i <= N; item_i++ ){
        for ( int w_i = 0; w_i <= K; w_i++){
            if( item_i == 0 || w_i == 0 )
                dp[item_i][w_i] = 0;
            else if ( items[item_i-1][0] <= w_i) {
                dp[item_i][w_i] = max_ab( items[item_i-1][1] + dp[item_i-1][w_i-items[item_i-1][0]], dp[item_i-1][w_i] );
            }
            else
                dp[item_i][w_i] = dp[item_i-1][w_i];
        }
    }

    cout << dp[N][K];
}
