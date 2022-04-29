/* smsh0722
 * 4103
 * ATM
 * */
#include <iostream>
#include <cstring>
#include <vector>
#include <stack>
using namespace std;

struct edge{
    int dst;
    edge* nextEdge;
};

class Graph{
    public:
        Graph( int N );
        ~Graph();
        void addEdge( int src, int dst );
        Graph* getSCC( int* sccSetIdx, int* sccCount );
        void topological_sort( stack<int>& topological_order, bool* visited, int curNode );
        Graph* getTransposeGraph();
        void sccDFS( bool* visited, int curNode, int sccIdx, Graph* sccG_r, int* sccSetIdx );
        void getAccumlatedSum( int S, int* sccAccumulatedSum, int* sccSum );
    private:
        int N;
        edge** adjList;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N, M;
    cin >> N >> M;

    Graph g = Graph(N);
    // Input Edge
    {
        int src, dst;
        for ( int i = 0; i < M; i++ ){
            cin >> src >> dst;
            g.addEdge( src, dst );
        }
    }
    // Input Money

    int* ATM;
    {
        ATM = new int[N+1];
        int money;
        for ( int atmI = 1; atmI <= N; atmI++ ){
            cin >> money;
            ATM[atmI] = money;
        }
    }

    int S; // Start Pos
    cin >> S;
    int P; // # of Restaurant
    cin >> P;

    int* restaurant_list;
    // Input restaurant
    {
        restaurant_list = new int[P];
        for ( int i = 0; i < P; i++ )
            cin >> restaurant_list[i];
    }

    Graph* sccG;
    int* sccSetIdx;
    int sccCount;
    // get scc Graph
    {        
        sccSetIdx = new int[N+1];
        memset( sccSetIdx, 0, sizeof(int)*(N+1) );   

        sccCount = 0;

        sccG = g.getSCC( sccSetIdx, &sccCount );
    }

    // Solve
    int max = 0;
    {
        int* sccSum = new int[sccCount+1];
        memset( sccSum, 0, sizeof(int)*(sccCount+1) );
        for ( int i = 1; i <= N; i++ )
            sccSum[sccSetIdx[i]] += ATM[i];

        int* sccAccumulatedSum = new int[sccCount+1];
        memset( sccAccumulatedSum, 0, sizeof(int)*(sccCount+1) );

        sccG->getAccumlatedSum( sccSetIdx[S], sccAccumulatedSum, sccSum );

        for ( int i = 0; i < P; i++ ){
            int sccIdx = sccSetIdx[ restaurant_list[i] ];
            // cout << sccAccumulatedSum[sccIdx] << " "; // Debug
            max = max > sccAccumulatedSum[sccIdx] ? max : sccAccumulatedSum[sccIdx];
        }

        delete[] sccSum;
        delete[] sccAccumulatedSum;  
    }

    // Print answer
    cout << max;

    // Avoid memleaks
    delete sccG;
    delete[] sccSetIdx;

    return 0;
}

Graph::Graph( int N )
{
    this->N = N;

    adjList = new edge*[N+1];   
    for ( int i = 0; i <= N; i++ )
        adjList[i] = nullptr;
}
Graph::~Graph()
{
    for ( int i = 0; i <= N; i++ ){
        edge* curEdge = adjList[i];
        while ( curEdge != nullptr ){
            edge* nextEdge = curEdge->nextEdge;
            delete curEdge;
            curEdge = nextEdge;
        }
    }
    delete[] adjList;
}
void Graph::addEdge( int src, int dst )
{
    edge* newEdge = new edge{ dst, adjList[src] };
    adjList[src] = newEdge;
}
Graph* Graph::getSCC( int* sccSetIdx, int* sccCount )
{
    stack<int> topological_order;
    // Get Topological order
    {
        bool* visited;
        visited = new bool[N+1];
        memset( visited, false, N+1 );

        for ( int i = 1; i <= N; i++ ){
            if ( visited[i] == false )
                topological_sort( topological_order, visited, i );
        }

        delete[] visited;
    }
    
    Graph* gr = getTransposeGraph();
    
    Graph* sccG;
    // get scc graph
    {
        Graph* sccG_r = new Graph(N);

        bool* visited;
        visited = new bool[N+1];
        memset( visited, false, N+1 );

        while ( topological_order.empty() == false ){
            int curNode = topological_order.top();
            topological_order.pop();

            if ( visited[curNode] == false ){
                (*sccCount)++;
                gr->sccDFS( visited, curNode, *sccCount, sccG_r, sccSetIdx );    
            }
        }

        sccG = new Graph(*sccCount);
        sccG = sccG_r->getTransposeGraph();
        
        // Avoid memleaks
        delete sccG_r;
        delete[] visited;
    }

    // Aoivd mem leaks
    delete gr;
    
    // Return
    return sccG;
}
void Graph::topological_sort( stack<int>& topological_order, bool* visited, int curNode )
{
    visited[curNode] = true;

    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ) {
        if ( visited[curEdge->dst] == false )
            topological_sort( topological_order, visited, curEdge->dst );
        
        curEdge = curEdge->nextEdge;
    }

    topological_order.push( curNode );
}
Graph* Graph::getTransposeGraph()
{
    Graph* gr = new Graph(N);

    for ( int src = 1; src <= N; src++ ){
        edge* curEdge = adjList[src];
        while ( curEdge != nullptr ){
            gr->addEdge( curEdge->dst, src );

            curEdge = curEdge->nextEdge;
        }
    }

    return gr;
}
void Graph::sccDFS( bool* visited, int curNode, int sccIdx, Graph* sccG_r, int* sccSetIdx )
{
    visited[curNode] = true;
    sccSetIdx[curNode] = sccIdx;

    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if( visited[curEdge->dst] == false )
            sccDFS( visited, curEdge->dst, sccIdx, sccG_r, sccSetIdx );
        else {
            int dstSCCIdx = sccSetIdx[curEdge->dst];
            if ( dstSCCIdx != sccIdx )
                sccG_r->addEdge( sccIdx, dstSCCIdx );
        }
        curEdge = curEdge->nextEdge;
    }
}
void Graph::getAccumlatedSum( int S, int* sccAccumulatedSum, int* sccSum )
{
    stack<int> topological_order;
    {
        bool* visited = new bool[N+1];
        memset( visited, false, N+1 );
        topological_sort( topological_order, visited, S );
        delete[] visited;
    }

    while ( topological_order.empty() == false ){
        int curNode = topological_order.top();
        topological_order.pop();
        
        sccAccumulatedSum[curNode] += sccSum[curNode];

        edge* curEdge = adjList[curNode];
        while ( curEdge != nullptr ){
            sccAccumulatedSum[curEdge->dst] = sccAccumulatedSum[curEdge->dst] > sccAccumulatedSum[curNode] ?
                                                sccAccumulatedSum[curEdge->dst] : sccAccumulatedSum[curNode];
            curEdge = curEdge->nextEdge;
        }
    }
}