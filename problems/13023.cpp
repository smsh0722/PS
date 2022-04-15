/* smsh0722
 * 13023
 * ABCED
 * */
#include <iostream>
#include <cstring>
using namespace std;

struct edge{
    int trgNode;
    edge* nextEdge;
};

int DFS( edge** adjList, bool* dfs_stack, int curNode, int curDepth );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N, M;
    cin >> N >> M;

    edge** adjList;
    // Input
    {
        adjList = new edge*[N];
        for ( int i = 0; i < N; i++ )
            adjList[i] = nullptr;
        
        int a, b;
        for ( int i = 0; i < M; i++ ){
            cin >> a >> b;
            edge* a2b = new edge{ b, adjList[a] };
            adjList[a] = a2b;
            edge* b2a = new edge{ a, adjList[b] };
            adjList[b] = b2a;
        }
    }    

    int max_depth = 0;
    // Solve
    {   
        bool* dfs_stack = new bool[N];
        memset( dfs_stack, false, sizeof(bool)*N );

        for ( int i = 0; i < N; i++ ){
            max_depth = DFS( adjList, dfs_stack, i, 0 );
            if ( max_depth >= 4 )
                break;
        }

        // Avoid mem leaks
        delete[] dfs_stack;
    }

    if ( max_depth >= 4 )
        cout << 1;
    else 
        cout << 0;
    
    return 0;
}
int DFS( edge** adjList, bool* dfs_stack, int curNode, int curDepth )
{
    dfs_stack[curNode] = true; // Push stack

    int max = curDepth;
    // DFS
    {
        edge* curEdge = adjList[curNode];
        while ( curEdge != nullptr ){
            if ( dfs_stack[curEdge->trgNode] == false ){
                int rst = DFS( adjList, dfs_stack, curEdge->trgNode, curDepth+1 );
                max = max > rst ? max : rst;
                if ( max >= 4 )
                    break;
            }

            curEdge = curEdge->nextEdge;
        }
    }

    dfs_stack[curNode] = false; // Pop stack
    return max;
}