/* smsh0722
 * 1937
 * 욕심쟁이 판다
 * */
#include <iostream>
using namespace std;

int solve( int** forest, int** dp, int size, int r, int c );

int main( void )
{
    int n;
    cin >> n;

    int** forest = new int*[n];
    int** dp = new int*[n];
    for ( int i = 0; i < n; i++ ){
        forest[i] = new int[n];
        dp[i]     = new int[n];
        for ( int j = 0; j < n; j++ ){
            cin >> forest[i][j];
            dp[i][j] = 0;
        }
    }

    // Solve
    int max = 0;
    int tmp;
    for ( int i = 0; i < n; i++ ){
        for ( int j = 0; j < n; j++ ){
            if ( dp[i][j] != 0 )
                continue;
            tmp = solve( forest, dp, n, i, j );
            max = max < tmp ? tmp : max;
        }
    }

    // Answer
    cout << max;
}

int solve( int** forest, int** dp, int size, int r, int c )
{
    /* next Site
     * [0][] = down
     * [1][] = up
     * [2][] = right
     * [3][] = left
     * */
    int adjSite[4][2];
    adjSite[0][0] = r + 1; adjSite[0][1] = c;
    adjSite[1][0] = r - 1; adjSite[1][1] = c;
    adjSite[2][0] = r;     adjSite[2][1] = c + 1;
    adjSite[3][0] = r;     adjSite[3][1] = c - 1;

    int max = 0;
    for ( int i = 0; i < 4; i++ ){
        int trgR = adjSite[i][0];
        int trgC = adjSite[i][1];

        if ( trgR < 0 || trgR >= size )
            continue;
        if ( trgC < 0 || trgC >= size )
            continue;
        
        if ( forest[r][c] >= forest[trgR][trgC] )
            continue;
        
        if ( dp[trgR][trgC] != 0 )
            max = max < dp[trgR][trgC] ? dp[trgR][trgC] : max;
        else {
            int rst = solve( forest, dp, size, trgR, trgC );
            max = max < rst ? rst : max;
        }
    }

    return ( dp[r][c] = max + 1 );
}