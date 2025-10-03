/* NOTE:
SOL) Floyd-Warshall
주의) src-mid-dst 중 mid의 cityTime에 대해 오름차순으로 조사해야 한다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct CityTime{
    int city;
    int time;
};

const int INF = INT32_MAX;

// # of Cities
int N;
// # of roads
int M;
// # of Queries
int Q;

vector<vector<int>> adjMat;
vector<vector<int>> ansMat;
vector<CityTime> cityTimes;

bool CompareCityTimeAsc( const CityTime& a, const CityTime& b )
{
    return a.time < b.time;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Input
        // Val
    cin >> N >> M >> Q;
        // City times
    cityTimes.resize(N+1, {0,0});
    for ( int ci = 1; ci <= N; ci++ ){
        cityTimes[ci].city = ci;
        cin >> cityTimes[ci].time;
    }
    sort( cityTimes.begin(), cityTimes.end(), CompareCityTimeAsc );
        // Roads
    adjMat.resize(N+1, vector<int>(N+1, INF ) );
    ansMat.resize(N+1, vector<int>(N+1, INF) );
    for ( int i = 1; i <= N; i++ ){
        adjMat[i][i] = 0;
        ansMat[i][i] = 0;
    }
    for ( int mi = 0; mi < M; mi++ ){
        int u, v, t;
        cin >> u >> v >> t;

        adjMat[u][v] = t;
        adjMat[v][u] = t;
    }

    // Floyd-Warshall
    for ( auto cityITime: cityTimes ){
        int i = cityITime.city;
        for ( auto cityJTime: cityTimes ){
            int j = cityJTime.city;
            if ( adjMat[i][j] == INF )
                continue;

            for ( auto cityKTime: cityTimes ){
                int k = cityKTime.city;
                if ( adjMat[i][k] == INF )
                    continue;

                adjMat[j][k] = min(
                    adjMat[j][k],
                    adjMat[j][i] + adjMat[i][k]
                );
                ansMat[j][k] = min(
                    ansMat[j][k],
                    adjMat[j][i] + adjMat[i][k] + max( 
                        cityITime.time, max( cityJTime.time, cityKTime.time )
                    )
                );
            }
        }
    }

    // Answers
    for ( int qi = 0; qi < Q; qi++ ){
        int u, v;
        cin >> u >> v;
        if ( ansMat[u][v] == INF )
            cout << -1;
        else 
            cout << ansMat[u][v];
        cout << "\n";
    }

    return 0;
}