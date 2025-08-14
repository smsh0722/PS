/* NOTE: Binary Lifting
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

// num of nodes
int N;
// num of queries
int M;
int maxLevel;

vector<vector<int>> adjList;
// depthOfNode[node] = depth of Node's in tree, val == -1 ? unvisited
vector<int> depthOfNode;
// parents[node][i] = node's 2^i-th parent, val == -1 ? unvisited
vector<vector<int>> parents;

void DFS( int cur, int prev )
{
    depthOfNode[cur] = depthOfNode[prev]+1;
    parents[cur][0] = prev;

    for ( size_t i = 0; i < adjList[cur].size(); i++ ){
        int dst = adjList[cur][i];
        if ( depthOfNode[dst] == -1 ){
            DFS( dst, cur );
        }
    }
}

void BuildParents()
{

    for ( int level = 1; level <= maxLevel; level++ ){
        for ( int node = 1; node <= N; node++ ){
            if ( parents[node][level-1] != -1 )
                parents[node][level] = parents[parents[node][level-1]][level-1];
        }
    }
}

int LCA( int a, int b )
{
    // Set to same depth
    if ( depthOfNode[a] > depthOfNode[b] )
        swap(a, b);
    int depthDiff = depthOfNode[b] - depthOfNode[a];
    for ( int i = 0; i <= maxLevel; i++ ){
        if( depthDiff&(1<<i) )
            b = parents[b][i];
    }
    
    if ( a== b)
        return a;
    
    // find lca
    for ( int level = maxLevel; level >= 0; level-- ){
        if( parents[a][level] != parents[b][level] ){
            a = parents[a][level];
            b = parents[b][level];
        }
    }
    
    return parents[a][0];
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    maxLevel = log2(N);
    adjList.resize(N+1);
    depthOfNode.resize(N+1, -1);
    parents.resize(N+1, vector<int>(maxLevel+1, -1));
    for ( int i = 0; i < N-1; i++ ){
        int a, b;
        cin >> a >> b;
        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    // DFS
    DFS(1, 1);

    // BuildTable
    BuildParents();

    // LCA
    cin >> M;
    for ( int m = 0; m < M; m++ ){
        int a, b;
        cin >> a >> b;
        cout << LCA(a, b) << "\n";
    }

    return 0;
}