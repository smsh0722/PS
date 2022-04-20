/* smsh0722
 * 1948
 * 임계경로
 * */
#include <iostream>
#include <stack>
#include <vector>
#include <queue>
#include <cstring>
using namespace std;

struct edge{
    int dst;
    int w;
    edge* nextEdge;
};

void topological_sort( edge** adjList, bool* visited, stack<int>& topological_order, int curNode );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N, M;
    cin >> N;
    cin >> M;

    edge** adjList;
    // Input
    {
        adjList = new edge*[N+1];
        for ( int i = 0; i <= N; i++ )
            adjList[i] = nullptr;

        int src, dst, w;
        for ( int i = 0; i < M; i++ ){
            cin >> src >> dst >> w;
            
            edge* newEdge = new edge{ dst, w, adjList[src] };
            adjList[src] = newEdge;
        }
    }

    int src, dst;
    cin >> src >> dst;

    stack<int> topological_order;
    // Topological Sort
    {
        bool* visited = new bool[N+1];
        memset( visited, false, sizeof(bool)*(N+1) );

        topological_sort( adjList, visited, topological_order, src );

        delete[] visited;
    }

    int* max_dist;
    int* num_of_edges;
    vector<int>* prev_node;
    // Calculate max dist
    {
        max_dist = new int[N+1];
        memset( max_dist, 0, sizeof(int)*(N+1) );

        num_of_edges = new int[N+1];
        memset( num_of_edges, 0, sizeof(int)*(N+1) );

        prev_node = new vector<int>[N+1];

        while ( topological_order.empty() == false ){
            int curNode = topological_order.top(); topological_order.pop();
            
            edge* curEdge = adjList[curNode];
            while( curEdge != nullptr ){
                int cur_dist = max_dist[curNode] + curEdge->w;

                if ( max_dist[curEdge->dst] < cur_dist ){
                    max_dist[curEdge->dst] = cur_dist;

                    prev_node[curEdge->dst].clear();
                    prev_node[curEdge->dst].push_back(curNode);

                    num_of_edges[curEdge->dst] = 1;
                }
                else if ( max_dist[curEdge->dst] == cur_dist ){
                    prev_node[curEdge->dst].push_back(curNode);

                    num_of_edges[curEdge->dst]++;
                }
                
                curEdge = curEdge->nextEdge;
            }
        }
    }

    int num_edges_max = 0;
    // Find Route
    {
        queue<int> bfs_Q;
        bfs_Q.push(dst);

        bool* visited = new bool[N+1];
        memset( visited, 0, sizeof(bool)*(N+1) );

        // BFS
        while ( bfs_Q.empty() == false ){
            int curNode = bfs_Q.front(); bfs_Q.pop();
            
            // Add num_of_edges between prev nodes
            num_edges_max += num_of_edges[curNode];

            // Enque Prve_node that makes max path
            for ( int i = 0; i < prev_node[curNode].size(); i++ ){
                if( visited[ prev_node[curNode].at(i) ] == false ){
                    bfs_Q.push(  prev_node[curNode].at(i) );
                    visited[ prev_node[curNode].at(i) ] = true;
                }
            }
        }

        // Avoid mem leaks
        delete[] visited;
    }
    cout << max_dist[dst] << "\n"
        << num_edges_max;
    
    return 0;
}

void topological_sort( edge** adjList, bool* visited, stack<int>& topological_order, int curNode )
{
    visited[curNode] = true;
    
    edge* curEdge = adjList[curNode];
    while( curEdge != nullptr ){
        if ( visited[curEdge->dst] == false )
            topological_sort( adjList, visited, topological_order, curEdge->dst );
        
        curEdge = curEdge->nextEdge;
    }
    topological_order.push(curNode);
}