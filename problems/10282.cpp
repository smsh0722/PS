#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge{
    int to;
    int time;
};
struct PQNode{
    int node;
    int time;
    bool operator<( const PQNode& other ) const 
    {
        return time > other.time;
    }
};

const int INF = INT32_MAX;

// # of Test cases
int T;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    while ( 0 < T ){
        T--;
        // # of Computers
        int N;
        // # of Edges
        int D;
        // Starting Computer
        int C;
        cin >> N >> D >> C;

        vector<vector<Edge>> adjList(N+1);
        while ( 0 < D ){
            D--;
            
            int a, b, s;
            cin >> a >> b >> s;

            adjList[b].push_back({a, s});
        }
    
        vector<int> dijkstra(N+1, INF);

        priority_queue<PQNode, vector<PQNode>> pq;
        pq.push({C,0});
        dijkstra[C] = 0;
        while ( pq.empty() == false ){
            PQNode cur = pq.top();
            pq.pop();

            if ( dijkstra[cur.node] < cur.time )
                continue;
            
            for ( auto edge : adjList[cur.node] ){
                int nextTime = edge.time + cur.time;
                if ( dijkstra[edge.to] > nextTime ){
                    pq.push({edge.to, nextTime});
                    dijkstra[edge.to] = nextTime;
                }
            }
        }

        int count = 0;
        int time = 0;
        for ( int c = 1; c <= N; c++ ){
            if ( dijkstra[c] != INF ){
                count++;
                time = max(time, dijkstra[c] );
            }
        }
        cout << count << " " << time << '\n';
    }

    return 0;
}