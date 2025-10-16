/* NOTE:

Naive)
nCk의 모든 경우를 시도하면 된다.
그러나 경우의 수가 매우 많아 불가능 하다.

Greedy?)
안된다. 힘만 볼 때는 비효율적인 스탯을 사용하더라도, 
다른 스탯에선 효율적인 선택이 가능할 수 있는데, 이 모든 걸 고려하는 것이 불가능 하다.
그러면 어떻게 할 수 있을까?

SOL)
병사 수의 비해 range가 넓으므로 좌표 압축을 사용할 수 있을 것 같다.
그러면 100^3 가지의 스탯을 시도해보면 된다.
(마지막 C까지 loop를 돌리면 터진다. 시간복잡도가 100^4 보다 조금 크기 때문. 대신 마지막에 K번째 c를 선택하면 된다. )
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Stat{
    int a;
    int b;
    int c;
};

// # of enemies
int N;
// # of goal
int K;

vector<Stat> enemies;
vector<int> aStats;
vector<int> bStats;
vector<int> cStats;

bool SortStatByA( const Stat& x, const Stat& y )
{
    return x.a < y.a;
}
bool SortStatByB( const Stat& x, const Stat& y )
{
    return x.b < y.b;
}
bool SortStatByC( const Stat& x, const Stat& y )
{
    return x.c < y.c;
}

bool compByA( int value, const Stat& s )
{
    return value < s.a;
}
bool compByB( int value, const Stat& s )
{
    return value < s.b;
}
bool compByC( int value, const Stat& s )
{
    return value < s.c;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    enemies.resize(N);
    aStats.resize(N);
    bStats.resize(N);
    cStats.resize(N);
    for ( int ni = 0; ni < N; ni++ ){
        int a, b, c;
        cin >> a >> b >> c;
        enemies[ni] = {a, b, c};
        aStats[ni] = a;
        bStats[ni] = b;
        cStats[ni] = c;
    }
    sort( aStats.begin(), aStats.end() );
    sort( bStats.begin(), bStats.end() );
    sort( cStats.begin(), cStats.end() );
    aStats.erase( unique(aStats.begin(), aStats.end() ), aStats.end() );
    bStats.erase( unique(bStats.begin(), bStats.end() ), bStats.end() );
    cStats.erase( unique(cStats.begin(), cStats.end() ), cStats.end() );

    int ans = INT32_MAX;
    for ( auto a : aStats ){
        for ( auto b : bStats ){
            vector<Stat> tmp = enemies;

            sort(tmp.begin(), tmp.end(), SortStatByA );
            tmp.erase( upper_bound(tmp.begin(), tmp.end(), a, compByA), tmp.end() );
            if ( int(tmp.size()) < K )
                continue;

            sort(tmp.begin(), tmp.end(), SortStatByB );
            tmp.erase( upper_bound(tmp.begin(), tmp.end(), b, compByB), tmp.end() );
            if ( int(tmp.size()) < K )
                continue;

            sort(tmp.begin(), tmp.end(), SortStatByC );
            int c = tmp[K-1].c;

            int sum = a+ b+ c;
            ans = ans > sum ? sum : ans;
        }
    }
    cout << ans;

    return 0;
}