/* NOTE: dinic algorithm
(쉬운 버전: 17412)

SOL)

dinic을 떠올렸다.
그러나, 정점에서의 횟수 제한으로 인해 dinic을 그대로 쓸 수 없다.

대신 정점을 input과 output으로 나눠 input->ouput의 capacity를 정해주면,
문제를 해결할 수 있다.
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
// # of splitCity
int NSplit;

vector<vector<Edge>> adjList;
vector<int> levels;

const int srcOut = 1*2+1;
const int dstIn = 2*2;

inline int CalIn( int u ) { return u*2; }
inline int CalOut( int u ) { return u*2+1; }

inline void AddEdge( int u, int v )
{
    int capacity = u == v ? 1 : INF;
    int uin = CalIn(u); int uout = CalOut(u);
    int vin = CalIn(v); int vout = CalOut(v);

    Edge e = {vin, 0, capacity, int(adjList[vin].size())};
    Edge eRev = {uout, 0, 0, int(adjList[uout].size()) };
    adjList[uout].push_back(e);
    adjList[vin].push_back(eRev);
}

bool BFS()
{
    // Reset Level
    for ( int i = 0; i <= NSplit; i++ )
        levels[i] = -1;

    // Set Level
    queue<int> q;
    q.push(srcOut);
    levels[srcOut] = 0;
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
    
    return levels[dstIn] != -1;
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
    NSplit = CalOut(N);
    // Build AdjList
    adjList.resize(NSplit+1);
    for ( int u = 1; u <= N; u++ ){
        int uin = CalIn(u);
        int uout = CalOut(u);

        Edge e = {uout, 0, 1, adjList[uout].size() };
        Edge eRev = {uin, 0, 0, adjList[uin].size() };
        adjList[uin].push_back(e);
        adjList[uout].push_back(eRev);
    }
    for ( int pi = 0; pi < P; pi++ ){
        int u, v;
        cin >> u >> v;

        AddEdge(u, v);
        AddEdge(v, u);
    }

    // Dinic
    int totalFlow = 0;
    levels.resize(NSplit+1);
    while ( BFS() ){
        // cout << "can send flow\n";
        vector<int> starts(NSplit+1,0);
        int flow = 0;
        while ( (flow = sendFlow(srcOut, dstIn, starts, INF)) ){
            // cout << "Add flow: " << flow << endl; // DEBUG
            totalFlow += flow;
        }
    }

    cout << totalFlow;
    return 0;
}