/* Sol) Dijkstra 응용
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX = INT32_MAX;

struct Edge{
    int to;
    int width;
};
struct PQNode{
    int v;
    int width;
};
struct ComparePQNode{
    bool operator()( const PQNode& a, const PQNode& b )
    {
        return a.width < b.width;
    }
};

// # of Vertices
int p;
// # of Edges
int w;

// Capital of Baekjoon
int c;
// Capital of Cube
int v;

vector<vector<Edge>> adjList;
vector<int> maxWidthToDst;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> p >> w;
    cin >> c >> v;
    adjList.resize(p);
    for ( int wi = 0; wi < w; wi++ ){
        int l, m, n;
        cin >> l >> m >> n;
        adjList[l].push_back({m,n});
        adjList[m].push_back({l,n});
    }

    maxWidthToDst.resize(p, -1);
    priority_queue<PQNode,vector<PQNode>, ComparePQNode> pq;
    pq.push({c, MAX});
    maxWidthToDst[c] = MAX;
    while ( pq.empty() == false ){
        PQNode top = pq.top();
        pq.pop();

        if ( top.width < maxWidthToDst[top.v] )
            continue;
        
        for( auto e : adjList[top.v] ){
            int minW = min(e.width, top.width);

            if ( maxWidthToDst[e.to] < minW ){
                pq.push({e.to, minW} );                
                maxWidthToDst[e.to] = minW;
            }
        }
    }

    cout << maxWidthToDst[v];

    return 0;
}