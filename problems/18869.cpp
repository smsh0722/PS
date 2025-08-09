/* NOTE:
unique 의 시간 복잡도는 O(N)이다.
Reference: https://cplusplus.com/reference/algorithm/unique/?kw=unique
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int M; // num of spaces
int N; // num of planets
int ans = 0;
// {[space Idx][planet idx] : planet size}
vector<vector<int>> spaces;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> M >> N;
    spaces.resize(M, vector<int>(N,0));
    for ( int si = 0; si < M; si++ ){
        for ( int pi = 0; pi < N; pi++ ){
            cin >> spaces[si][pi];
        }
    }

    // Compress coordinate
    for ( int si = 0; si < M; si++ ){
        vector<int> space = spaces[si];
        sort( space.begin(), space.end() );
        space.erase( unique(space.begin(), space.end()), space.end() );

        for ( int pi = 0; pi < N; pi++ ){
            int compressedSize = lower_bound(space.begin(), space.end(), spaces[si][pi]) - space.begin();
            spaces[si][pi] = compressedSize;
        }
    }

    for ( int si = 0; si < M; si++ ){
        for ( int sj = si+1; sj < M; sj++ ){
            bool bSuccess = true;
            for ( int pi = 0; bSuccess == true && pi < N; pi++ ){
                bSuccess = spaces[si][pi] == spaces[sj][pi];
            }
            ans += bSuccess ? 1 : 0;
            // printf( "space[%d] : space[%d] == %d\n", si, sj, (int)bSuccess);// Debug
        }
    }

    cout << ans;

    return 0;
}