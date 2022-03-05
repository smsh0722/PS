/* smsh0722
 * 2133
 * 타일 채우기
 * */
#include <iostream>
using namespace std;

int main( void )
{
    int N;
    
    cin >> N;

    // Case1: N == odd
    if ( N % 2 == 1 ){
        cout << 0;
        return 0;
    }
    
    // Case2: N == even
    int* dp = new int[N+1];
    dp[0] = 1;
    dp[2] = 3;

    for ( int i = 4; i <= N; i += 2 ){
        dp[i] = dp[i-2] * 3;
        for ( int j = 4; j <= i; j += 2 )
            dp[i] += dp[i-j] * 2;
    }

    cout << dp[N];

    return 0;
}