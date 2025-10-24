/* NOTE:
2D dp를 떠올렸다.

그러나 이렇게 하면 메모리가 초과된다.
어떻게 하면 메모리를 줄일 수 있을까?

잘 생각해보면, 1D로도 구현할 수 있다.
*/
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 100;
const int MAX_K = 10000;

// # of coin category
int n;
// Target value
int k;

vector<int> coins;

// memo[coin][k] = # of cases
vector<int> dp(MAX_K+1, 0);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> k;
    coins.resize(n);
    for ( int ni = 0; ni < n; ni++ )
        cin >> coins[ni];

    dp[0] = 1;
    for ( int c : coins ){
        for ( int v = c; v <= k; v++ ){
            dp[v] += dp[v-c];
        }
    }

    cout << dp[k];
    return 0;
}

/*
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 100;
const int MAX_K = 10000;

// # of coin category
int n;
// Target value
int k;

vector<int> coins;

// memo[coin][k] = # of cases
vector<vector<int>> memo( MAX_N, vector<int>(MAX_K+1, -1) );

// ci: coin idx, tv: target value
int DFS( int ci, int tv )
{
    if ( tv == 0 )
        return 1;
    if ( ci >= n || tv < 0)
        return 0;
    if ( memo[ci][tv] != -1 )
        return memo[ci][tv];
    

    int rst = 0;
    
    int nextTargetValue = tv;
    for ( int i = 0; nextTargetValue >= 0; i++ ){
        rst += DFS(ci+1, nextTargetValue );
        nextTargetValue -= coins[ci];
    }
    
    return memo[ci][tv] = rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> k;
    coins.resize(n);
    for ( int ni = 0; ni < n; ni++ )
        cin >> coins[ni];

    cout << DFS( 0, k );

    return 0;
}
*/