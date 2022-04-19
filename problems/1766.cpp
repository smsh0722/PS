/* smsh0722
 * 1766 
 * 문제집
 * */
#include <iostream>
#include <queue>
#include <cstring>
using namespace std;

struct edge{
    int dst;
    edge* nextEdge;
};

int main ( void ) 
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;

    edge** adjList;
    int* in_degree;
    // Dynamic Alloc
    {
        adjList = new edge*[N+1];
        for ( int i = 0; i <= N; i++ )
            adjList[i] = nullptr;

        in_degree = new int[N+1];
        memset( in_degree, 0, sizeof(int)*(N+1) );
    }
    // Input
    {
        int M;
        cin >> M;

        int a, b;
        for ( int i = 0; i < M; i++ ){
            cin >> a >> b;

            edge* a2b = new edge{ b, adjList[a] };
            adjList[a] = a2b;

            in_degree[b]++;
        }
    }
    /* Solve
     * kahn's algorithm for topological sorting
     * using priority_queue
     * */
    queue<int> sorted_order;
    {
        priority_queue<int> bfs_q;
        for ( int i = 1; i <= N; i++ ){
            if ( in_degree[i] == 0 ) 
                bfs_q.push(-i);
        }

        // BFS
        while ( bfs_q.empty() == false ){
            int curNode = bfs_q.top(); bfs_q.pop();
            curNode = -curNode;

            sorted_order.push(curNode);
            
            // Check adjList
            edge* curEdge = adjList[curNode];
            while( curEdge != nullptr ){
                --in_degree[curEdge->dst];
                if ( in_degree[curEdge->dst] == 0 )
                    bfs_q.push(-(curEdge->dst));
                curEdge = curEdge->nextEdge;
            }
        }
    }

    // Print topological order
    while( sorted_order.empty() == false ){
        cout << sorted_order.front() << " ";
        sorted_order.pop();
    }

    return 0;
}