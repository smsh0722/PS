#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int INF = INT32_MAX;

// # of events
int N;
// # of edge
int K;
// # of queries
int S;

vector<vector<int>> dist;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    
    dist.resize(N+1, vector<int>(N+1, INF) );
        for ( int i = 0; i < K; i++ ){
        int u, v;
        cin >> u >> v;
        dist[u][v] = 1;
    }

    for ( int m = 1; m <= N; m++ ){
        for ( int u = 1; u <= N; u++ ){
            for ( int v = 1; v <= N; v++ ){
                if ( dist[u][m] != INF && dist[m][v] != INF ){
                    dist[u][v] = min( dist[u][v], dist[u][m] + dist[m][v] );
                }
            }
        }
    }

    cin >> S;
    for ( int si = 0; si < S; si++ ){
        int u, v;
        cin >> u >> v;
        
        int ans = 0;
        if ( dist[u][v] != INF)
            ans = -1;
        else if ( dist[v][u] != INF )
            ans = 1;
        
        cout << ans << '\n';
    }

    return 0;
}