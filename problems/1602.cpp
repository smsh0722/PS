/* NOTE:
src to dst 갈 때, 특정 center를 무조건 지나도록 조사하여 그 중 최소 찾기.
그러나, center to src, center to dst 의 최단이 꼭 최단이 아닐 수도 있음.
돌아가는 것도 가능.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

// Time Complexity
// O((V+E)logV)*Q
// 90000*500 + 500*40000

struct Road{
    int dst;
    int w;
};
struct PQNode{
    int city;
    int w;
};
struct ComparePQNodeAsc{
    bool operator()(const PQNode& a, const PQNode& b )
    {
        return a.w > b.w;
    }
};
struct DijkstraNode{
    int w;
    int maxCityTime;
};

const int INF = INT32_MAX;

// # of Cities
int N;
// # of roads
int M;
// # of Queries
int Q;

vector<int> cityTimes;
vector<vector<Road>> roads;

// Dijkstras[src][dst] = min dist from src to dst;
vector<vector<DijkstraNode>> Dijkstras;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> Q;
    // Get Input
        // City Times
    cityTimes.resize(N+1, 0);
    for( int ci = 1; ci <= N; ci++ ){
        cin >> cityTimes[ci];
    }    
        // Roads
    roads.resize(N+1);
    for( int mi = 0; mi < M; mi++ ){
        int u, v, w;
        cin >> u >> v >> w;
        roads[u].push_back({v,w});
        roads[v].push_back({u,w});
    }

    // Build Dijkstras
    Dijkstras.resize(N+1);
    for ( int src = 1; src <= N; src++ ){
        Dijkstras[src].resize(N+1, {INF, 0});

        priority_queue<PQNode, vector<PQNode>, ComparePQNodeAsc> pq;
        pq.push({src, 0});
        Dijkstras[src][src] = {0, cityTimes[src]};
        while ( pq.empty() ==false ){
            PQNode top = pq.top();
            pq.pop();

            if( Dijkstras[src][top.city].w < top.w )
                continue;
            
            for ( auto road : roads[top.city]){
                int newCost = road.w + top.w;
                if ( newCost < Dijkstras[src][road.dst].w ){
                    pq.push({road.dst, newCost});
                    Dijkstras[src][road.dst].w = newCost;
                    Dijkstras[src][road.dst].maxCityTime = max(
                        Dijkstras[src][top.city].maxCityTime, cityTimes[road.dst]
                    );
                }
            }
        }
    }

    // Queries
    for ( int qi = 0; qi < Q; qi++ ){
        int src, dst;
        cin >> src >> dst;

        int minTime = INF;
        for ( int center = 1; center <= N; center++ ){
            if ( Dijkstras[center][src].w == INF || Dijkstras[center][dst].w == INF )
                continue;
            int time = Dijkstras[center][src].w 
                    + Dijkstras[center][dst].w 
                    + max( Dijkstras[center][src].maxCityTime, Dijkstras[center][dst].maxCityTime);
            minTime = min( minTime, time);
        }

        if ( minTime == INF )
            cout << -1;
        else 
            cout << minTime;
        cout << "\n";
    }    
    
    return 0;
}