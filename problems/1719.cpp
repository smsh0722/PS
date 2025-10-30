#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge{
    int dst;
    int w;
};
struct DijkstraData{
    int p;
    int sum;
};
struct QData {
    int p;
    int v;
    int sum;
};
struct CompareQData{
    bool operator()( const QData& a, const QData& b )
    {
        return a.sum > b.sum; // ASC
    }
};

const int INF = INT32_MAX;

// # of vertices
int N;
// # of edges
int M;

vector<vector<int>> ans;
vector<vector<Edge>> adjList;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    adjList.resize(N+1);
    for ( int mi = 0; mi < M; mi++ ){
        int u, v, w;
        cin >> u >> v >> w;
        adjList[u].push_back({v,w});
        adjList[v].push_back({u,w});
    }

    // Dijkstra and build Ans
    ans.resize(N+1, vector<int>(N+1, 0) );
    for ( int src = 1; src <= N; src++ ){
        vector<DijkstraData> dijkstra( N+1, {0, INF});
        priority_queue<QData, vector<QData>, CompareQData> pq;

        dijkstra[src] = {src, 0};
        pq.push({src, src, 0});
        while ( pq.empty() == false ){
            QData cur = pq.top();
            pq.pop();

            if ( cur.sum > dijkstra[cur.v].sum )
                continue;
            
            for ( auto e : adjList[cur.v] ){
                QData next;
                next.p = cur.p == src ? e.dst : cur.p;
                next.v = e.dst;
                next.sum = cur.sum + e.w;
                if( next.sum < dijkstra[next.v].sum ){
                    dijkstra[next.v] = { next.p, next.sum };
                    pq.push(next);
                }
            }
        }

        for ( int dst = 1; dst <= N; dst++ ){
            ans[src][dst] = dijkstra[dst].p;
        }
    }
    
    // Print
    for ( int r = 1; r <= N; r++ ){
        for ( int c = 1; c <= N; c++ ){
            if ( r== c )
                cout << "-";
            else 
                cout << ans[r][c];
            cout << " ";
        }
        cout << "\n";
    }

    return 0;
}