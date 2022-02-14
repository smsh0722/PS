#include <iostream>
#include <vector>
using namespace std;


void DFS( const int curr, const vector< vector<int> >& adjList, vector<vector<int>>& binaryParent, vector<int>& depth );
int lca( int a, int b, const vector<int>& depth, vector<vector<int>>& binaryParent );
void setBinaryParent( const int curr, int depth, vector<vector<int>>& binaryParent );

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    cout.tie(NULL);

    int n; cin >> n;
    vector<int> depth(n+1, -1); // 1~n
    vector<vector<int>> binaryParent(n+1, vector<int>(16, 1) ); // [1~n][2^i]
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
        depth[1] = 0;
        DFS( 1, adjList, binaryParent, depth );
    }
    
    int m; cin >> m;
    {
        int a, b;
        for ( int i = 0; i < m; i++ ){
            cin >> a >> b;
            cout << lca( a, b, depth, binaryParent ) << "\n";
        }
    }

    return 0;
}

void DFS( const int curr, const vector< vector<int> >& adjList, vector<vector<int>>& binaryParent, vector<int>& depth )
{
    for ( int eidx= 0; eidx < adjList[curr].size(); eidx++ ){
        int trg = adjList[curr][eidx];
        if ( depth[trg] == -1 ){
            depth[trg] = depth[curr] + 1;
            binaryParent[trg][0] = curr;
            setBinaryParent( trg, depth[trg], binaryParent );
            DFS( trg, adjList, binaryParent, depth );
        }
    }
}
void setBinaryParent( const int curr, int depth, vector<vector<int>>& binaryParent )
{
    int ith = 0;
    while ( depth > 1 ){
        int ithP = binaryParent[curr][ith];
        binaryParent[curr][ith+1] = binaryParent[ithP][ith];
        depth /= 2;
        ith++;
    }
}

int lca( int a, int b, const vector<int>& depth, vector<vector<int>>& binaryParent )
{
    if( depth[a] > depth[b] ){
        int tmp = a;
        a = b;
        b = tmp;
    }

    {
        int diff = depth[b] - depth[a];
        for ( int i = 16; i >= 0; i-- ){
            if ( diff & ( 1 << i ) ){
                b = binaryParent[b][i];
            }
        }
    }

    if ( a == b ){
        return a;
    }

    for ( int i = binaryParent[a].size(); i >= 0 ; i-- ){
        if ( binaryParent[a][i] != binaryParent[b][i] ){
            a = binaryParent[a][i];
            b = binaryParent[b][i];
        }
    }

    return binaryParent[a][0];
}

