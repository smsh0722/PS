/* NOTE:
일반적으로 다익스트라는 거리값만 신경쓰면 됐다. 추가해봤자 부모루트 정도만 생각하면 됐다.

그러나 이번 문제는 특정 구간을 지나는 지 여부를 체크해야한다. 
최단경로는 사실 여러 루트로 가능한데, 거리만가지고 dijkstra를 하면 문제가 생긴다.
따라서, 거리뿐 아니라 기존엔 안 쓰던 특정 경로 지났는지 여부로 pq push 를 결정한다.

또한 이때 조건 느슨하면 큐 터지므로 신경써야 한다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Edge{
    int to;
    int dist;
};

struct NodeOfPQ{
    bool bSmellVisited;
    int node;
    int dist;
};
struct CompareNodeOfPQ{
    bool operator()( const NodeOfPQ& a, const NodeOfPQ& b )
    {
        return a.dist > b.dist; // dist DESC
    }
};

struct Dijkstra{
    bool bSmellVisited;
    int dist;
};

const int INF = INT32_MAX;

// # of tests
int T;

// # v, # e
int n, m;
// # candidates of goal
int t;

// starting V
int s;
// u, v of smell
int g, h;

inline bool IsSemllRoute( int u, int v )
{
    if ( u > v )
        swap( u, v);
    return (g== u && h == v );
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    for ( int ti = 0; ti < T; ti++ ){
        cin >> n >> m >> t;
        cin >> s >> g >> h;
        if ( g > h )
            swap(g, h);

        vector<vector<Edge>> adjList(n+1);
        for ( int mi = 0; mi < m; mi++ ){
            int a, b, d;
            cin >> a >> b >> d;
            adjList[a].push_back({b,d});
            adjList[b].push_back({a,d});
        }

        vector<int> candsOfGoal(t);
        for ( int i = 0; i < t; i++ )
            cin >> candsOfGoal[i];
        sort( candsOfGoal.begin(), candsOfGoal.end() );

        // Dijkstra 생성
        vector<Dijkstra> dijkstra(n + 1, {false, INF} );
        priority_queue<NodeOfPQ, vector<NodeOfPQ>, CompareNodeOfPQ> pq;

        pq.push({false, s, 0} );
        dijkstra[s] = { false, 0 };
        while (pq.empty() == false ){
            NodeOfPQ top = pq.top();
            pq.pop();

            if ( top.dist > dijkstra[top.node].dist )
                continue;

            for ( auto edge : adjList[top.node] ){
                int newDist = top.dist + edge.dist;
                bool bSmellEdge = IsSemllRoute(top.node, edge.to );

                bool bSmellVisited = bSmellEdge | top.bSmellVisited;

                // NOTE: 큐에 추가될 요소가 평소보다 많다.
                // 이때 조건을 조금이라도 느슨하게 하면 큐가 터져버린다. 
                // 이런 문제가 잘 없기 때문에 복습 잘 하자.
                    // 더 짧은 경로이므로 무조건 추가
                if ( newDist < dijkstra[edge.to].dist ){
                    pq.push({ bSmellVisited, edge.to, newDist});
                    dijkstra[edge.to] = { bSmellVisited, newDist  }; 
                }
                    // 더 짧은 경로는 아니더라도, 
                    // 원하는 구간을 기존엔 안 지났지만 새로 지나는 상황이라면 다시 dijkstra 해야한다.
                    // 현재 노드 및 그 뒤 노드에도 반영해야하기 때문이다.
                    // 이 부분 조건 느슨하면 터져버린다.
                else if ( newDist == dijkstra[edge.to].dist && bSmellVisited == true && dijkstra[edge.to].bSmellVisited == false){
                    pq.push({ bSmellVisited, edge.to, newDist});
                    dijkstra[edge.to] = { bSmellVisited, newDist  };
                }
            }
        }
        
        // 각 cand 에 대하여 g, h 경로 지나는 지 확인
        for ( auto candV : candsOfGoal ){
            if( dijkstra[candV].bSmellVisited == true )
                cout << candV << " ";            
        }
        cout << "\n";

    }

    return 0;
}