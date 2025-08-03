#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge{
    int node;
    int w;
};
struct EdgeWeightAscOrder{
    bool operator() ( const Edge& a, const Edge& b )
    {
        return a.w > b.w; // ASC
    };
};

const int MAX_INT = ~(1<<31);
const int MAX_N = 5000;
const int MAX_M = 100000;

int n; // num of nodes
int m; // num of edges
int s; // start node
int t; // term node

vector<vector<Edge>> adjList( MAX_N+1 );
vector<int> dist(MAX_N+1, MAX_INT); 
priority_queue<Edge, vector<Edge>, EdgeWeightAscOrder> pq;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;
    for ( int i = 0; i < m; i++ ){
        int a, b, c;
        cin >> a >> b >> c;
        adjList[a].push_back({b, c});
        adjList[b].push_back({a, c});
    }
    cin >> s >> t;
    
    pq.push({s,0});
    dist[s] = 0;
    while ( pq.empty() == false ) {
        Edge t = pq.top();
        pq.pop();

        if ( dist[t.node] < t.w )
            continue;
        for ( size_t i = 0; i < adjList[t.node].size(); i++ ){
            Edge e = adjList[t.node][i];

            int newW = e.w + t.w;
            if ( dist[e.node] > newW ){
                dist[e.node] = newW;
                pq.push({e.node, newW});
            }
        }
    }

    cout << dist[t];

    return 0;
}