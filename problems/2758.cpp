#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// Num of picks
int n;
// Max Num
int m;
// TestCase
int T;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for ( int ti = 0; ti < T; ti++ ){
        // Solve test case [ti]
        cin >> n >> m;

        // dpTable[pickCount][curNum]
        vector<vector<int64_t>> dpTable(n+1, vector<int64_t>(m+1, 0) );
        for ( int pickCount = n; pickCount > 0; pickCount-- ){
            for ( int curNum = (1<<(pickCount-1)); curNum <= (m>>(n-pickCount)); curNum++ ){
                if ( pickCount == n )
                    dpTable[pickCount][curNum] = 1;
                else {
                    for ( int nextNum = curNum*2; nextNum <= (m>>(n-pickCount-1)); nextNum++ )
                        dpTable[pickCount][curNum] += dpTable[pickCount+1][nextNum];
                }
            }
        }

        int64_t ans = 0;
        for ( int i = 1; i <= m; i++ )
            ans += dpTable[1][i];
        cout << ans << "\n";
    }

    return 0;
}