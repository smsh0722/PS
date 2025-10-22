#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge{
    int dst;
    int dist;
};

struct PQNode{
    bool bPassStopover;
    int v;
    int distSum;
};
struct Dijkstra{
    bool bPassStopover;
    int distSum;
};

struct ComparePQNode{
    bool operator() ( const PQNode& a, const PQNode& b )
    {
        return a.distSum > b.distSum;
    }
};

const int INF = INT32_MAX;

// # of vertices
int V;
// # of edges
int E;
// 건우 위치
int P;

vector<vector<Edge>> adjList;

vector<Dijkstra> dijkstra;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> V >> E >> P;
    adjList.resize(V+1);
    for ( int ei = 0; ei < E; ei++ ){
        int a, b, c;
        cin >> a >> b >> c;
        adjList[a].push_back({b,c});
        adjList[b].push_back({a,c});
    }

    // Dijkstra
    dijkstra.resize(V+1, {false, INF} );
    priority_queue<PQNode, vector<PQNode>, ComparePQNode> pq;
    pq.push({P==1, 1,0});
    dijkstra[1] = { P==1, 0 };
    while ( pq.empty() == false ){
        PQNode top = pq.top();
        pq.pop();

        if ( top.distSum > dijkstra[top.v].distSum )
            continue;
        for ( auto edge : adjList[top.v] ){
            int newDistSum = edge.dist + top.distSum;
            bool bNewPassStopover = top.bPassStopover | (P == edge.dst);
            if ( newDistSum < dijkstra[edge.dst].distSum ){
                pq.push( {bNewPassStopover, edge.dst, newDistSum} );
                dijkstra[edge.dst] = { bNewPassStopover, newDistSum };
            }
            else if ( newDistSum == dijkstra[edge.dst].distSum 
                && bNewPassStopover == true 
                && dijkstra[edge.dst].bPassStopover == false )
            {
                pq.push( {bNewPassStopover, edge.dst, newDistSum} );
                dijkstra[edge.dst] = { bNewPassStopover, newDistSum };
            }
        }
    }

    if ( dijkstra[V].bPassStopover == true )
        cout << "SAVE HIM";
    else 
        cout << "GOOD BYE";

    return 0;
}