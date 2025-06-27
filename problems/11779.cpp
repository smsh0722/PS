#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

struct Vec2{
    union{
        struct{ int x, y; };
        struct{ int a, b; };
        struct{ int node, dist; };
    };
};

struct mycomp{
    bool operator()(Vec2& a, Vec2& b ){
        return a.dist > b.dist;
    };
};

const int MAX_INT = ~(1<<31);
const int MAX_CITY = 1000;
int n, m; // n: num of city, m: num of bus(edge)
int src, dst;

vector<vector<Vec2>> adjList(MAX_CITY); // Vec2{dst, dist}
vector<Vec2> minDistVec( MAX_CITY, Vec2{-1, MAX_INT}); // Vec2{prevNode, dist};

int main (void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> n;
    cin >> m;
    {
        int src, dst, dist;
        for ( int i = 0; i < m; i++ ){
            cin >> src >> dst >> dist;
            src--; dst--;
            adjList[src].push_back( Vec2{dst, dist} );
        }
    }
    cin >> src >> dst; src--; dst--;
    
    priority_queue<Vec2, vector<Vec2>, mycomp > pq;
    pq.push( Vec2{src, 0} );
    minDistVec[src] = Vec2{src, 0};
    while ( pq.empty() == false ){
        int src = pq.top().node;
        int dist = pq.top().dist;
        pq.pop();
        
        if ( minDistVec[src].dist < dist ) // NOTE: 불피요한 edge 방문 방지
            continue;

        for ( size_t i = 0; i < adjList[src].size(); i++ ){
            Vec2 edge = adjList[src][i];

            int curDist = minDistVec[edge.node].dist;
            int newDist = minDistVec[src].dist + edge.dist;
            if( curDist > newDist ){
                pq.push(Vec2{edge.node, newDist});
                minDistVec[edge.node] = Vec2{ src, newDist };
            }
        }
    }

    stack<int> path;
    {
        int curNode = dst;
        path.push(dst);
        while ( curNode != src ){
            int prevNode = minDistVec[curNode].node;
            path.push(prevNode);
            curNode = prevNode;
        }
    }

    cout << minDistVec[dst].dist << endl;
    cout << path.size() << endl;
    while ( path.empty() == false ){
        int curNode = path.top();
        path.pop();

        cout << curNode + 1 << " ";
    }
}