#include <iostream>
#include <vector>
using namespace std;

const int DIVISOR = 1000000;

int N;

// dpMemo[# of left in left][# of left in right][up1 or down0] = # of case
vector<vector<vector<int>>> dpMemo(
    101, vector<vector<int>>( 
        101, vector<int>(
            2, -1
        )
    )
);

int DFS( int l, int r, bool bShouldUP )
{
    if ( dpMemo[l][r][int(bShouldUP)] >= 0 ){
        return dpMemo[l][r][int(bShouldUP)];
    }
    if ( l == 0 && r == 0 )
        return 1;

    int ans = 0;
    if (bShouldUP == true ){
        int tryR = 1;
        while ( tryR <= r ){
            ans += DFS( l + (tryR-1), r - tryR, false );
            ans %= DIVISOR;

            tryR++;
        }
    }
    else { // bShouldUp == false: Go Down
        int tryL = 1;
        while ( tryL <= l ){
            ans += DFS( tryL-1, r + (l-tryL), true );
            ans %= DIVISOR;

            tryL++;
        }
    }

    // printf("\t l: %d, r: %d, bShoulup: %d ans: %d\n", l, r,bShouldUP, ans); // DEBUG
    return (dpMemo[l][r][int(bShouldUP)] = ans);
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    if ( N == 1 ){
        cout << 1;
        return 0;
    }
    if ( N == 2 ){
        cout << 2;
        return 0;
    }

    int ans = 0;
    for ( int s0 = 1; s0 <= N; s0++ ){
        for ( int s1 = 1; s1 <= N; s1++ ){
            if ( s1 == s0 )
                continue;
            
            // printf("s0: %d, s1: %d\n", s0, s1);
            // int debug;
            if ( s0 < s1 ){
                // debug = DFS( s1 - 2, N - s1, false );
                ans += DFS( s1 - 2, N - s1, false );
            }
            else { // s0 > s1
                // 5 3 10
                // debug = DFS( s1 - 1, N - s1 - 1, true );
                ans += DFS( s1 - 1, N - s1 - 1, true );
            }
            // printf("ans: %d\n", debug); // DEBUG

            ans %= DIVISOR;
        }
    }

    cout << ans;

    return 0;
}