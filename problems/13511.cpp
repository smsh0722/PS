#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

struct Parent{
    int nodeNum;
    int64_t weightSum;
};

struct Edge{
    int dst;
    int64_t weight;
};

// Num of Nodes
int N;
// Num of Queries
int M;

vector<vector<Edge>> adjList;

int maxLevel;
vector<int> depthOfNodes;
vector<vector<Parent>> parents;

void DFS( int cur, int prev, int w )
{
    depthOfNodes[cur] = depthOfNodes[prev]+1;
    parents[cur][0] = {prev, w };

    for ( size_t i = 0; i < adjList[cur].size(); i++ ){
        Edge e = adjList[cur][i];
        if ( depthOfNodes[e.dst] == -1 ){ // visited == false
            DFS( e.dst, cur, e.weight );
        }
    }
}

void BuildParents( )
{
    for ( int level = 1; level <= maxLevel; level++ ){
        for ( int node = 1; node <= N; node++ ){
            if ( parents[node][level-1].nodeNum != -1 ){
                parents[node][level] = parents[parents[node][level-1].nodeNum][level-1];
                parents[node][level].weightSum += parents[node][level-1].weightSum;
            }
        }
    }
}

void PrintDebug()
{
    for ( int node = 1; node <= N; node++ ){
        printf("Node[%d]: ", node );
        for ( int level = 0; level <= maxLevel; level++ ){
            Parent p = parents[node][level];
            printf("2^%dth(%d, %I64d) ", level, p.nodeNum, p.weightSum );
        }
        printf("\n");
    }
}

int LCA( int a, int b )
{
    if ( depthOfNodes[a] > depthOfNodes[b] )
        swap(a, b);
    int depthDiff = depthOfNodes[b] - depthOfNodes[a];
    for ( int i = 0; i <= maxLevel; i++ ){
        if ( depthDiff&(1<<i) ){
            b = parents[b][i].nodeNum;
        }
    }

    if ( a == b)
        return a;
    
    for ( int level = maxLevel; level >= 0; level-- ){
        if ( parents[a][level].nodeNum != parents[b][level].nodeNum ){
            a = parents[a][level].nodeNum;
            b = parents[b][level].nodeNum;
        }
    }

    return parents[a][0].nodeNum;
}

int64_t GetDist( int node, int parent )
{
    int64_t rst = 0;

    int depthDiff = depthOfNodes[node] - depthOfNodes[parent];
    for ( int level = 0; level <= maxLevel; level++ ){
        if ( depthDiff&(1<<level) ){
            rst += parents[node][level].weightSum;
            node = parents[node][level].nodeNum;
        }
    }

    return rst;
}

int FindKthParent( int node, int k )
{
    // printf( "node: %d, k: %d\n", node, k ); // Debug
    for ( int level = 0; level <= maxLevel; level++ ){
        if ( k&(1<<level) ){
            node = parents[node][level].nodeNum;
        }
    }
    return node;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    // Get Tree
    cin >> N;
    
    adjList.resize(N+1);

    maxLevel = log2(N);
    depthOfNodes.resize(N+1,-1);
    parents.resize(N+1, vector<Parent>(maxLevel+1, {-1, 0} ) );

    for ( int i = 0; i < N-1; i++ ){
        int a, b;
        int64_t w;
        cin >> a >> b >> w;
        adjList[a].push_back( {b, w} );
        adjList[b].push_back( {a, w} );
    }

    // Prepare LCA
    DFS( 1, 1, 0);

    BuildParents();

    // PrintDebug(); // Debug

    // Answer Queries
    cin >> M;
    for ( int m = 0; m < M; m++ ){
        int opt;
        cin >> opt;
        if ( opt == 1 ){
            int u, v;
            cin >> u >> v;

            int p = LCA(u, v);
            int64_t ans = GetDist(u, p ) + GetDist(v, p);
            cout << ans << "\n";
        }
        else { // opt == 2: 
            int u, v, k;
            cin >> u >> v >> k;
            k--;

            int lca = LCA(u, v);
            // printf("lca: %d\n", lca ); // Debug
            int uToP = depthOfNodes[u] - depthOfNodes[lca];
            if ( uToP >= k ){
                cout << FindKthParent( u, k ) << "\n";
            }
            else {
                int vToP = depthOfNodes[v] - depthOfNodes[lca] ;
                cout << FindKthParent( v, vToP - (k - uToP) ) << "\n";
            }
        }
    }
    return 0;
}