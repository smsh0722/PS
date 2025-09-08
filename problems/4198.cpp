/* NOTE:
Naive는 dfs를 하며 cars[i]에 대하여 두가지를(포함, 미포함)을 시도해보는 것이다.
그런나 시간 복잡도가 O(2^N)이 된다.

DP 로 풀려면 (F, R, ci) 정도의 세가지 축이 있으면 될 것 같다. 그러나 O(N^3)으로 불가능 하다.

Parametric Search로 길이 또는 F, R 시도시 풀기 어렵다..

lis 생각이 나긴 하였지만, Input[] = {3, 4, 5, 2, 1, 6, 7, 8} 일때 증감이 반복되어 어케찾지 했다.

다만 잘 생각해보면 첫 시작점이 분명히 존재한다. 매 시작점을 기준으로 lis, lds를 찾아서 최대를 찾으면 된다.
시간 복잡도는 O(N^2)이다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Num of Cars
int N;

vector<int64_t> cars;
// lis[i]: lis start at car[i]
vector<int> lis;
// lds[i]: lds start at car[i]
vector<int> lds;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    cars.resize(N, 0);
    lis.resize(N, 0);
    lds.resize(N, 0);
    for ( int i = 0; i < N; i++ )
        cin >> cars[i];

    // Build LIS, LDS
    for ( int i = N-1; i >= 0; i-- ){
        int lisMax = 1;
        int ldsMax = 1;
        for ( int j = i+1; j < N; j++ ){
            if ( cars[i] < cars[j] ){
                lisMax = max( lisMax, lis[j]+1);
            }
            if ( cars[i] > cars[j] ){
                ldsMax = max( ldsMax, lds[j]+1);
            }
        }
        lis[i] = lisMax;
        lds[i] = ldsMax;
    }

    // Get Ans
    int ans = 0;
    for ( int i = 0; i < N; i++ ){
        ans = max( ans, lis[i] + lds[i] - 1);
    }
    cout << ans;

    return 0;
}