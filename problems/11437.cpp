#include <iostream>
#include <vector>
using namespace std;

struct node{
    int parent;
    int depth;
    node(): parent(0), depth(0) {}
    node( int p, int d ): parent(p), depth(d) {}
};

void DFS( const int curr, const vector< vector<int> >& adjList, vector< bool >& visited, vector<node>& nodeVec );
int lca( int a, int b, vector<node>& nodeVec );

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n; cin >> n;
    vector<node> nodeVec(n+1); // 1~n
    {
        vector< vector<int> > adjList( n + 1 ); // 1 ~ n;
        {
            int nodeA, nodeB;
            for ( int i = 0; i < n - 1; i++ ){
                cin >> nodeA >> nodeB;
                adjList[nodeA].push_back( nodeB );
                adjList[nodeB].push_back( nodeA );
            }
        }
        nodeVec[1] = node(1,0);
        vector<bool> visited( n+1, false );
        DFS( 1, adjList, visited, nodeVec );
    }
    
    int m; cin >> m;
    {
        int a, b;
        for ( int i = 0; i < m; i++ ){
            cin >> a >> b;
            cout << lca( a, b, nodeVec ) << "\n";
        }
    }

    return 0;
}

void DFS( const int curr, const vector< vector<int> >& adjList, vector< bool >& visited, vector<node>& nodeVec )
{
    visited[curr] = true;
    int depth = nodeVec[curr].depth;
    for ( int eidx= 0; eidx < adjList[curr].size(); eidx++ ){
        int trg = adjList[curr][eidx];
        if ( visited[trg] == false ){
            nodeVec[trg] = node( curr, depth + 1 );
            DFS( trg, adjList, visited, nodeVec );
        }
    }
}

int lca( int a, int b, vector<node>& nodeVec )
{
    if( nodeVec[a].depth > nodeVec[b].depth ){
        int tmp = a;
        a = b;
        b = tmp;
    }

    int aP = a;
    int bP = b;
    {
        int aDepth = nodeVec[a].depth;
        int bDepth = nodeVec[b].depth;
        while ( aDepth < bDepth ){
            bP = nodeVec[bP].parent;
            bDepth--;
        }
    }
    while( aP != bP ){
        aP = nodeVec[aP].parent;
        bP = nodeVec[bP].parent;
    }

    return aP;
}

