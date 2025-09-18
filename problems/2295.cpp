#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int N;
vector<int64_t> u;

map<int64_t, bool> m;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie( NULL );

    cin >> N;
    u.resize(N, -1);
    for ( int n = 0; n < N; n++ )
        cin >> u[n];
    sort(u.begin(), u.end() );

    for ( int ai = 0; ai < N; ai++ ){
        for ( int bi = ai; bi < N; bi++ ){
            int64_t sum = u[ai] + u[bi];
            m[sum] = true;
        }
    }

    int64_t ans = -1;
    for ( int di = 0; di < N; di++ ){
        for ( int ai = 0; ai < N; ai++ ){
            int64_t trg = u[di] - u[ai];
            
            if ( m.find(trg) == m.end() )
                continue;

            if ( m[trg] == true ){
                ans = max( ans, u[di] );
                break;
            }
        }
    }

    cout << ans;

    return 0;
}