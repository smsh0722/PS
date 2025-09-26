#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge{
    int dst;
    int64_t t;
};

struct NodePQ{
    int node;
    int64_t time;
};
struct CompareNodePQ{
    bool operator()( const NodePQ a, const NodePQ& b )
    {
        return a.time > b.time; // Asc order
    }
};

const int64_t INF = INT64_MAX;

// # of node
int N;
// # of edge or Period
int64_t M;

// adjList[node][edge idx] = edge
// node: [1:N]
vector<vector<Edge>> adjList;

vector<int64_t> dijkstra;

inline int64_t GetNextTime( const Edge& e, int64_t curTime )
{
    if ( curTime <= e.t )
        return e.t;
    
    int64_t diff = curTime - e.t;
    int64_t x = (diff / M);
    x += (diff%M) > 0 ? 1 : 0;
    return (M*x + e.t);
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    
    adjList.resize(N+1);
    for( int mi =0; mi < M; mi++ ){
        int u, v;
        cin >> u >> v;
        adjList[u].push_back({v, mi});
        adjList[v].push_back({u, mi});
    }

    // Dijkstra
    dijkstra.resize(N+1, INF );
    priority_queue<NodePQ, vector<NodePQ>, CompareNodePQ> pq;

    pq.push({1,0});
    dijkstra[1] = 0;
    while ( pq.empty() == false ){
        NodePQ top = pq.top();
        pq.pop();

        if ( dijkstra[top.node] < top.time )
            continue;

        for ( auto edge : adjList[top.node] ){
            int64_t newArrivalTime= GetNextTime( edge, top.time ) + 1;
            // cout << top.node << " to " << edge.dst << " will arrive at " << newArrivalTime << endl;// DEBUG

            if ( dijkstra[edge.dst] > newArrivalTime ){
                pq.push( {edge.dst, newArrivalTime} );
                dijkstra[edge.dst] = newArrivalTime;
            }   
        }
    }

    cout << dijkstra[N];

    return 0;
}