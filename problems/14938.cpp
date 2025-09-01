/* NOTE:
dijkstra의 시간복잡도는 O(ElogV) 이다.
이 경우엔 모든 시작점을 시도해봐야 한다. 
따라서 시간 복잡도는 O(VElogV)가 된다.
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_DIST = ~(1<<31);

struct Edge {
    int dst;
    int dist;
};

struct PQ{
    int node;
    int dist;
};
struct ComparePQ{
    bool operator()( const PQ& a, const PQ& b )
    {
        return a.dist > b.dist;
    }
};

// Num of Cities
int N;
// Range of Search
int M;
// Num of roads
int R;

vector<int> items;
vector<vector<Edge>> adjList;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> R;

    items.resize(N+1, 0 );
    adjList.resize(N+1);

    for ( int i = 1; i <= N; i++ )
        cin >> items[i];
    for ( int i = 0; i < R; i++ ){
        int a, b, dist;
        cin >> a >> b >> dist;

        adjList[a].push_back(Edge{b, dist});
        adjList[b].push_back(Edge{a, dist});
    }

    int maxGet = 0;

    for ( int s = 1; s <= N; s++ ){
        vector<int> dijkstra(N+1, MAX_DIST);
        
        priority_queue<PQ, vector<PQ>, ComparePQ> pq;
        pq.push( {s,0} );
        dijkstra[s] = 0;
        while ( pq.empty() == false ){
            PQ t = pq.top();
            pq.pop();

            if ( dijkstra[t.node] < t.dist )
                continue;
            
            for ( auto edge : adjList[t.node] ){
                int newDist = t.dist + edge.dist;
                if ( dijkstra[edge.dst] > newDist ){
                    pq.push( {edge.dst, newDist } );
                    dijkstra[edge.dst] = newDist;
                }
            }
        }

        int localGet = 0;
        for ( int i = 1; i <= N; i++ ){
            if ( dijkstra[i] <= M ){
                localGet += items[i];
            }
        }
        maxGet = maxGet > localGet ? maxGet : localGet;
    }

    cout << maxGet;

    return 0;
}