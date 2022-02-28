/* smsh0722
 * 2225
 * 합분해
 * */
#include <iostream>
using namespace std;

int main( void )
{
    int** table; // N+1 x k+1
    int n, k;
    cin >> n >> k;

    // Dynamic Allocation
    table = new int*[n+1];
    for ( int i = 0; i < n+1; i++ )
        table[i] = new int[k+1];
    
    // Set base case
    for ( int c = 1; c <= k; c++ )
        table[0][c] = 1;
    for ( int r = 0; r <= n; r++ )
        table[r][1] = 1;

    // Calculate
    for ( int r = 1; r <= n; r++ ){
        for ( int c = 2; c <= k; c++ )
            table[r][c] = ( (int64_t)table[r][c-1] + table[r-1][c] ) % 1000000000;
    }

    cout << table[n][k];
}