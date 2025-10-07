/* NOTE: dinic algorithm

(심화버전: 2316)
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int INF = INT32_MAX;

struct Edge{
    int v;
    int flow;
    int capacity;
    int rev;
};

// # of cities
int N;
// # of edges
int P;

vector<vector<Edge>> adjList;
vector<int> levels;

bool BFS()
{
    // Reset Level
    for ( int i = 0; i <= N; i++ )
        levels[i] = -1;

    // Set Level
    queue<int> q;
    q.push(1);
    levels[1] = 0;
    while ( q.empty() == false ){
        int u = q.front();
        q.pop();

        for ( auto edge : adjList[u] ){
            if ( levels[edge.v] != -1 || edge.flow >= edge.capacity )
                continue;
            levels[edge.v] = levels[u] + 1;
            q.push(edge.v);
        }
    }

    // for ( int i = 0; i <= N; i++ ) // DEBUG
    //     cout << i << "'s level: " << levels[i] << endl;
    
    return levels[2] != -1;
}

int sendFlow( int u, int v, vector<int>& starts, int maxFlow )
{
    if ( u == v )
        return maxFlow;
    
    for ( ; starts[u] < (int)adjList[u].size(); starts[u]++ ){
        Edge& edge = adjList[u][starts[u]];
        if( levels[u] + 1 != levels[edge.v] )
            continue;
        int leftFlow = edge.capacity - edge.flow;
        if( leftFlow <= 0 )
            continue;
        
        int flow = sendFlow(edge.v, v, starts, min(maxFlow, leftFlow) );
        if ( flow > 0 ){
            edge.flow += flow;
            adjList[edge.v][edge.rev].flow -= flow;

            return flow;
        }
    }

    return 0;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> P;
    // Build AdjList
    adjList.resize(N+1);
    for ( int pi = 0; pi < P; pi++ ){
        int u, v;
        cin >> u >> v;
        Edge e = {v, 0, 1, int(adjList[v].size())};
        Edge erev = {u, 0, 0, int(adjList[u].size()) };
        adjList[u].push_back(e);
        adjList[v].push_back(erev);
    }

    // Dinic
    int totalFlow = 0;
    levels.resize(N+1);
    while ( BFS() ){
        // cout << "can send flow\n";
        vector<int> starts(N+1,0);
        int flow = 0;
        while ( (flow = sendFlow(1, 2, starts, INF)) ){
            // cout << "Add flow: " << flow << endl; // DEBUG
            totalFlow += flow;
        }
    }

    cout << totalFlow;
    return 0;
}