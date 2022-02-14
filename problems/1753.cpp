#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAXPLUS1 = 3000001;

typedef struct edge{
    int dst;
    int w;
    edge ( int dst, int w ) : dst(dst),w(w) {};
} edge;

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int v, e; cin >> v >> e;
    int sv; cin >> sv;

    vector< vector< edge > > adjList(v+1); // src -> <dst, w>
    {
        int u, v, w;
        for ( int i = 0; i < e; i++ ){
            cin >> u >> v >> w;
            adjList[u].push_back( edge( v, w ) );
        }
    }
    
    vector<int> vSum( v + 1, MAXPLUS1 );
    {
        vSum[sv] = 0;

        priority_queue< pair<int, int> > vQ; // cost, v
        vQ.push( make_pair(0, sv) );
        while ( vQ.empty() == false ){
            int src = vQ.top().second;
            int cost = -vQ.top().first;
            vQ.pop();
            if ( vSum[src] >= cost ){
                for ( int idx = 0; idx < adjList[src].size(); idx++ ){
                    int dst = adjList[src][idx].dst;
                    int w = adjList[src][idx].w;
                    int tmpSum = vSum[src] + w;
                    if ( vSum[dst] > tmpSum ){
                        vQ.push( make_pair(-tmpSum, dst) );
                        vSum[dst] = tmpSum;
                    }
                }
            }
        }
    }

    for ( int i = 1; i <= v; i++ ){
        if ( vSum[i] == MAXPLUS1 ){
            cout << "INF\n";
        }
        else {
            cout << vSum[i] << '\n';
        }
    }
    return 0;
}