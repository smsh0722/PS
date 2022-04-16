/* smsh0722
 * 2252
 * 줄 세우기
 * */
#include <iostream>
#include <cstring>
#include <stack>
using namespace std;

struct edge{
    int trgNode;
    edge* nextEdge;
};

void topologicalSort( edge** adjList, bool* visited, int curNode, stack<int>& topological_stack );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    cin >> N;
    
    edge** adjList;
    // Input
    {
        adjList = new edge*[N+1];
        for ( int i = 0; i <= N; i++ )
            adjList[i] = nullptr;
        
        int M;
        cin >> M;
        for ( int i = 0; i < M; i++ ){
            int a, b;
            cin >> a >> b;
            edge* a2b = new edge{ b, adjList[a] };
            adjList[a] = a2b;    
        }
    }

    stack<int> topological_stack;
    // Solve
    {
        bool* visited = new bool[N+1];
        memset( visited, false, sizeof(bool)*(N+1) );

        for ( int i = 1; i <= N; i++ ){
            if ( visited[i] == false )
                topologicalSort( adjList, visited, i, topological_stack );
        }
        delete[] visited;
    }

    // Print
    for ( int i = N-1; i >= 0; i-- ){
        cout << topological_stack.top() << " ";
        topological_stack.pop();
    }

    return 0;
}
void topologicalSort( edge** adjList, bool* visited, int curNode, stack<int>& topological_stack )
{
    visited[curNode] = true;

    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( visited[curEdge->trgNode] == false ){
            topologicalSort( adjList, visited, curEdge->trgNode, topological_stack );
        }
        curEdge = curEdge->nextEdge;
    }
    topological_stack.push(curNode);
}