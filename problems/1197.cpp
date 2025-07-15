/* Prim's Algorithm
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Edge{
    int dst;
    int cost;
};

struct EdgeCompare{
    bool operator() (const Edge& a, const Edge& b )
    {
        return a.cost > b.cost; // 오름차순
    };
};


const int MAX_V = 10000;
const int MAX_E = 100000;

int V;
int E;

vector<vector<Edge>> adjList(MAX_V+1); // use [1,V]
vector<bool> visited(MAX_V+1, false);
priority_queue<Edge, vector<Edge>, EdgeCompare> pq;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> V >> E;

    for ( int i = 0; i < E; i++ ){
        int a, b, cost;
        cin >> a >> b >> cost;
        adjList[a].push_back(Edge{b,cost});
        adjList[b].push_back(Edge{a,cost});
    }

    int rst = 0;
    pq.push( Edge{1,0});
    while (pq.empty() == false ){
        Edge e = pq.top();
        pq.pop();

        if ( visited[e.dst] == true )
            continue;
        
        visited[e.dst] = true;
        rst += e.cost;

        for ( size_t i = 0; i < adjList[e.dst].size(); i++ ){
            Edge adjEdge = adjList[e.dst][i];

            if( visited[adjEdge.dst] == false ){
                pq.push( adjEdge );
            }
        }
    }

    cout << rst;

    return 0;
}