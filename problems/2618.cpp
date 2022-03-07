/* smsh0722
 * 2618
 * 경찰차
 * */
#include <iostream>
#include <stdlib.h>
using namespace std;

const int NA = -1;

struct point {
    int x;
    int y;
};

int getCost( point* points, int pa, int pb );
int solve( point* points, int** dp, int W, int trg_event, int a, int b );

int main( void )
{
    ios_base::sync_with_stdio(false); cout.tie(NULL);

    int N, W;
    cin >> N >> W;
    
    point* points = new point[W+2];
    for ( int i = 1; i <= W; i++ )
        cin >> points[i].x >> points[i].y;
    points[0].x = 1; points[0]. y = 1;
    points[W+1].x = N; points[W+1].y = N;

    int** dp = new int*[1001];
    for ( int i = 0; i <= W; i++ ){
        dp[i] = new int[1001];
        for ( int j = 0; j <= W; j++ )
            dp[i][j] = NA;
    }

    cout << solve( points, dp, W, 1, 0, 0 ) << "\n";

    {
        int a = 0;
        int b = 0;
        for ( int i = 1; i <= W; i++ ){
            int l = getCost( points, a, i ) + dp[i][b];
            int r = getCost( points, (b == 0 ? W+1 : b), i ) + dp[a][i];
            if ( l < r ){
                a = i;
                cout << 1 << "\n";
            }
            else {
                b = i;
                cout << 2 << "\n";
            }
        }
    }
}

int getCost( point* points, int pa, int pb )
{
    int xDif = abs( points[pa].x - points[pb].x );
    int yDif = abs( points[pa].y - points[pb].y );

    return ( xDif + yDif );
}

int solve( point* points, int** dp, int W, int trg_event, int a, int b )
{
    if ( trg_event > W )
        return 0;
    if ( dp[a][b] != NA )
        return dp[a][b];
    
    int l = getCost( points, a, trg_event );
    int r = getCost( points, (b == 0 ? W+1 : b), trg_event );

    l += solve( points, dp, W, trg_event + 1, trg_event, b );
    r += solve( points, dp, W, trg_event + 1, a, trg_event );
    
    if ( l < r ){
        dp[a][b] = l;
        return l;
    }
    else {
        dp[a][b] = r;
        return r;
    }
}