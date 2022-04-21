/* smsh0722
 * 4196
 * 도미노
 * */
#include <iostream>
#include <stack>
#include <cstring>
using namespace std;

struct edge{
    int dst;
    edge* nextEdge;
};

class Graph{
    public:
        Graph( int n );
        ~Graph();
        void addEdge( int src, int dst );
        void solve();
        void getTopological_order( stack<int>& topological_order, bool* visited, int curNode );
        void do_domino( bool* visited, int curNode );
    private:
        int n;
        edge** adjList;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    int T;
    cin >> T;
    
    for ( int t_n = 1; t_n <= T; t_n++ ){
        int n, m;
        cin >> n >> m;

        Graph g = Graph(n);

        // Input
        for ( int i = 0; i < m; i++ ){
            int src, dst;
            cin >> src >> dst;
            g.addEdge( src, dst );
        }

        g.solve();
    }

    return 0;
}

Graph::Graph( int n )
{
    this->n = n;

    adjList = new edge*[n+1];
    for ( int i = 0; i <= n; i++ )
        adjList[i] = nullptr;
}
Graph::~Graph()
{
    for ( int i = 0; i <= n; i++ ){
        edge* curEdge = adjList[i];

        while ( curEdge != nullptr ){
            edge* nextEdge = curEdge->nextEdge;

            delete curEdge; // Delete

            curEdge = nextEdge;
        }
    }

    delete[] adjList; // Delete[]
    // cout << "Graph destructed.\n"; // Debug
}
void Graph::addEdge( int src, int dst )
{
    edge* newEdge = new edge{ dst, adjList[src] };
    adjList[src] = newEdge;
}
void Graph::solve()
{
    bool* visited;
    stack<int> topological_order;
    // Get Topological Order
    {
        visited = new bool[n+1];
        memset( visited, false, sizeof(bool)*(n+1) );

        for ( int i = 1; i <= n; i++ ){
            if ( visited[i] == false )
                getTopological_order( topological_order, visited, i );
        }
    }

    int trial_count = 0;

    // do_domino
    {
        memset( visited, false, sizeof(bool)*(n+1) );
        while ( topological_order.empty() == false ){
            int curNode = topological_order.top();
            topological_order.pop();

            if ( visited[curNode] == false ){
                do_domino( visited, curNode );
                trial_count++;
            }
        }
    }

    // Print trial_count
    cout << trial_count << "\n"; 

    delete[] visited;
}
void Graph::getTopological_order( stack<int>& topological_order, bool* visited, int curNode )
{
    // Set as visited
    visited[curNode] = true;
    // Recursive Call
    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( visited[curEdge->dst] == false )
            getTopological_order( topological_order, visited, curEdge->dst );
        
        curEdge = curEdge->nextEdge;
    }
    // Push to stack
    topological_order.push( curNode );
}
void Graph::do_domino( bool* visited, int curNode )
{
    visited[curNode] = true;

    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( visited[curEdge->dst] == false ){
            do_domino( visited, curEdge->dst );
        }
        curEdge = curEdge->nextEdge;
    }
}