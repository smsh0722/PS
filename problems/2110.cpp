/* NOTE:
bruteforce로 모든 조합 시도해보면 된다.
그러나 시간 복잡도가 너무 오래걸린다.

DFS 과정 중에 dp 가능하지 않을까?
너무 복잡하다.

대신, 가능한 거리의 lower_bound를 찾자. -> parametric_search
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Num of homes
int N;
// Num of routers
int C;

vector<int> homes;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> C;
    
    homes.resize(N);
    for ( int i = 0; i < N; i++ ){
        cin >> homes[i];
    }
    sort( homes.begin(), homes.end() );

    int ans = -1;
    int l = 1;
    int r = 1000000000;
    while ( l <= r ){
        int mid = (r-l)/2+l;

        int installedRouterCount = 1;
        int prevRouterIdx = 0;
        for ( int i = 1; i < N; i++ ){
            int dist = homes[i] - homes[prevRouterIdx];
            if ( dist >= mid ){
                prevRouterIdx = i;
                installedRouterCount++;
            }
        }

        if ( installedRouterCount >= C ){
            ans = mid;
            l = mid + 1;
        }
        else { // installedRouterCount < C
            r = mid - 1;
        }
    }

    cout << ans;

    return 0;
}