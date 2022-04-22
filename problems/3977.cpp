/* smsh0722
 * 3977
 * 축구 전술
 * */
#include <iostream>
#include <stack>
#include <cstring>
#include <vector>
#include <algorithm>
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
        void topological_sort( stack<int>& topological_order, bool* visited, int curNode );
        Graph* getTranspose();
        void getSCC( bool* visited, int curNode, vector<int>& sccComponents );
        void getIndegree( bool* in_degree );
    private:
        int n;
        edge** adjList;
        int* sccParent;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
    int T;
    cin >> T;
    for ( int t_i = 1; t_i <= T; t_i++ ){
        int N, M;
        cin >> N >> M;

        Graph g = Graph(N);

        // Input Edge
        for ( int i = 0; i < M; i++ ){
            int src, dst;
            cin >> src >> dst;

            g.addEdge( src, dst );
        }

        // Solve
        g.solve();
        
        // new Line
        cout << "\n";
    }
}

Graph::Graph( int n )
{
    this->n = n;
    
    adjList = new edge*[n];
    for ( int i = 0; i < n; i++ ) 
        adjList[i] = nullptr;

    sccParent = new int[n];
    for ( int i = 0; i < n; i++ )
        sccParent[i] = -1;
}
Graph::~Graph()
{
    for ( int i = 0; i < n; i++ ){
        edge* curEdge = adjList[i];
        while ( curEdge != nullptr ){
            edge* nextEdge = curEdge->nextEdge;
            delete curEdge;
            curEdge = nextEdge;
        }
    }
    delete[] adjList;

    delete[] sccParent;

    //cout << "destruct completed.\n"; // Debug
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
        visited = new bool[n];
        memset( visited, false, sizeof(bool)*n );

        for ( int i = 0; i < n; i++ ){
            if ( visited[i] == false )
                topological_sort( topological_order, visited, i );
        }
    }

    // Build SCC
    {
        memset( visited, false, sizeof(bool)*n );

        Graph* g_reverse = getTranspose();

        while ( topological_order.empty() == false ){
            int curNode = topological_order.top();
            topological_order.pop();
            
            if ( visited[curNode] == false ){
                vector<int> sccComponents;

                g_reverse->getSCC( visited, curNode, sccComponents );

                for ( int i = 0; i < sccComponents.size(); i++ ){
                    int curNode = sccComponents[i];
                    sccParent[ curNode ] = sccComponents[0];
                }
            }
        }

        delete g_reverse;
    }

    // get Indegree
    bool* in_degree;
    {
        in_degree = new bool[n];
        memset( in_degree, true, sizeof(bool)*n );

        getIndegree( in_degree );
    }

    int s_sccParent = -1;
    vector<int> s_points;
    // Find s_points
    {
        for ( int i = 0; i < n; i++ ){
            if ( in_degree[sccParent[i]] == false )
                continue;
            
            if ( s_sccParent == -1 ){
                s_sccParent = sccParent[i];
                s_points.push_back(i);
            }
            else if ( s_sccParent == sccParent[i] )
                s_points.push_back(i);
            else {
                s_sccParent = -1;
                break;
            }
        }
    }

    // Print Answer
    if ( s_sccParent == -1 )
        cout << "Confused" << "\n";
    else {
        sort( s_points.begin(), s_points.begin() + s_points.size() );
        for ( int i = 0; i < s_points.size(); i++ )
            cout << s_points[i] << "\n";
    }
    
    // Avoid mem leaks
    delete[] in_degree;
    delete[] visited;
}
void Graph::topological_sort( stack<int>& topological_order, bool* visited, int curNode )
{
    visited[curNode] = true;

    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( visited[curEdge->dst] == false )
            topological_sort( topological_order, visited, curEdge->dst );

        curEdge = curEdge->nextEdge;
    }

    topological_order.push( curNode );
}
Graph* Graph::getTranspose()
{
    Graph* g_reverse = new Graph(n);

    for ( int src = 0; src < n; src++ ){
        edge* curEdge = adjList[src];
        while ( curEdge != nullptr ){
            g_reverse->addEdge( curEdge->dst, src );
            curEdge = curEdge->nextEdge;
        }
    }

    return g_reverse;
}
void Graph::getSCC( bool* visited, int curNode, vector<int>& sccComponents )
{
    visited[curNode] = true;

    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( visited[ curEdge->dst ] == false )
            getSCC( visited, curEdge->dst, sccComponents );
        
        curEdge = curEdge->nextEdge;
    }

    sccComponents.push_back( curNode );
}
void Graph::getIndegree( bool* in_degree )
{
    for ( int src = 0; src < n; src++ ){
        edge* curEdge = adjList[src];
        while ( curEdge != nullptr ){   
            if ( sccParent[src] != sccParent[curEdge->dst] )
                in_degree[sccParent[curEdge->dst]] = false;
            
            curEdge = curEdge->nextEdge;
        }
    }
}