/* NOTE:
1 풀이보다 조금 더 구현이 간단.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge{
    int dst;
    int dist;
};

struct PQNode{
    int v;
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

vector<int> dijkstraFrom1;
vector<int> dijkstraFromP;

void CalDijkstra( vector<int>& dijkstra, const int src )
{
    priority_queue<PQNode, vector<PQNode>, ComparePQNode> pq;
    pq.push({src, 0});
    dijkstra[src] = 0;
    while ( pq.empty() == false ){
        PQNode top = pq.top();
        pq.pop();

        if ( top.distSum > dijkstra[top.v] )
            continue;
        for ( auto edge : adjList[top.v] ){
            int newDist = edge.dist + top.distSum;
            if( newDist < dijkstra[edge.dst] ){
                pq.push({edge.dst, newDist});
                dijkstra[edge.dst] = newDist;
            }

        }
    }
}

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
    dijkstraFrom1.resize(V+1, INF );
    dijkstraFromP.resize(V+1, INF );
    CalDijkstra( dijkstraFrom1, 1 );
    CalDijkstra( dijkstraFromP, P );

    int minDist = dijkstraFrom1[V];
    int minDist2 = dijkstraFrom1[P] + dijkstraFromP[V];
    if ( minDist2 == minDist )
        cout << "SAVE HIM";
    else 
        cout << "GOOD BYE";

    return 0;
}