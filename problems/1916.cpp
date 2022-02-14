/* 1916 최소비용 구하기
 * Dijkstra 
 * smsh0722
 * */
#include<iostream>
#include<vector>
#include<queue>
using namespace std;

const int INFINITE = 100000 * 1000;

struct edge {
    int dst;
    int w;
    edge( int a, int b ): dst(a), w(b) {}
};
struct compare{
    bool operator() (const edge& a, const edge& b ){
        return a.w > b.w;
    }
};
int main( void )
{
    int N, M; // N: # cities, M: # buses
    cin >> N >> M;
    int src, dst;
    vector<edge> adjList[N+1]; // 1 ~ N
    {
        int a, b, w;
        for ( int i = 0; i < M; i++ ){
            cin >> a >> b >> w;
            adjList[a].push_back( edge( b, w ) );
        }
    }
    cin >> src >> dst;

    /* Calculate shortest path */
    vector<int> distances( N + 1, INFINITE );
    distances[src] = 0;
    {
        priority_queue<edge, vector<edge>, compare > q;
        q.push( edge(src, 0) );
        while( q.empty() == false ){
            edge e = q.top(); q.pop();
            
            if ( distances[e.dst] < e.w )
                continue;
            
            for ( int i = 0; i < adjList[e.dst].size(); i++ ){
                int newDist = distances[e.dst] + adjList[e.dst][i].w;
                if ( newDist < distances[adjList[e.dst][i].dst] ){
                    distances[adjList[e.dst][i].dst] = newDist;
                    q.push( edge( adjList[e.dst][i].dst, newDist) );
                }
            }
        }
    }

    cout << distances[dst] << "\n";
    return 0;
}