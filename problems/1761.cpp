/* smsh0722
 * 1761
 * 정점들의 거리
 * */
#include <iostream>
#include <cstring>
#include <cmath>
using namespace std;

int INF = (-1)^(1<<31);
struct edge {
    int trgNode;
    int dist;
    edge* nextEdge;
};

edge** adjList;         // Adjacency List
int* distFromRoot;      // Distance(weight) of each Node from root
int* firstOccurOfNode; // First occurrence of each Node
int* dfsLog_node;      // Node at each occurrence
int* dfsLog_level;    // Level at each occureence
int* ST;             // Segment Tree

void DFS( bool* visited, int curNode, int* count, int curLevel );
int constructSTUtil( int idx, int l, int r );
int getMinST( int idx, int l, int r, int trgL, int trgR );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N;
    cin >> N;

    // Input
    {
        adjList = new edge*[N+1];
        for ( int i = 0; i <= N; i++ )
            adjList[i] = nullptr;

        int nodeA, nodeB, dist;
        for ( int i = 0; i < N - 1; i++ ){
            cin >> nodeA >> nodeB >> dist;
            edge* a2b = new edge{ nodeB, dist, adjList[nodeA] };
            edge* b2a = new edge{ nodeA, dist, adjList[nodeB] };
            adjList[nodeA] = a2b;
            adjList[nodeB] = b2a;
        }
    }

    // Pre-process
    // DFS
    {
        distFromRoot = new int[N+1];
        memset( distFromRoot, 0, sizeof(int)*(N+1) );
        firstOccurOfNode = new int[N+1];
        dfsLog_node = new int[2*N-1];
        dfsLog_level = new int[2*N-1];

        int count = 0;

        bool* visited = new bool[N+1];
        memset( visited, false, sizeof(bool)*(N+1) );

        DFS( visited, 1, &count, 1 );

        delete[] visited;
    }
    // Construct ST
    {
        int h = ceil( log2(2*N - 1) );
        int size = (1<<(h+1))-1;
        ST = new int[size];
        
        constructSTUtil( 0, 0, 2*N-1-1 );
    }

    // Answer Qeury
    {
        int M;
        cin >> M;
        
        int a, b;
        for ( int i = 0; i < M; i++ ){
            cin >> a >> b;
            if ( firstOccurOfNode[a] > firstOccurOfNode[b] ){
                int tmp = a;
                a = b;
                b = tmp;
            }

            int lca = dfsLog_node[ getMinST( 0, 0, 2*N-1-1, firstOccurOfNode[a], firstOccurOfNode[b] ) ];

            cout << (distFromRoot[a] + distFromRoot[b] - 2*distFromRoot[lca]) << "\n";
        }
    }
    return 0;
}
void DFS( bool* visited, int curNode, int* count, int curLevel )
{
    firstOccurOfNode[curNode] = *count; // Set firstOccurOfNode
    dfsLog_node[*count] = curNode; // Set dfsLog_node
    dfsLog_level[*count] = curLevel; // Set dfsLog_level
    visited[curNode] = true;
    ++(*count);

    // DFS
    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( visited[curEdge->trgNode] == true ){
            curEdge = curEdge->nextEdge;
            continue;
        }

        distFromRoot[curEdge->trgNode] = distFromRoot[curNode] + curEdge->dist; // set Dist
        DFS( visited, curEdge->trgNode, count, curLevel + 1 ); // DFS

        dfsLog_node[*count] = curNode;
        dfsLog_level[*count] = curLevel;
        ++(*count);

        curEdge = curEdge->nextEdge;
    }
}
int constructSTUtil( int idx, int l, int r )
{
    // Base Case
    if ( l == r ){
        ST[idx] = l;
        return l;
    }
    // Recursive Find
    int mid = ( r - l ) / 2 + l;
    int lval = constructSTUtil( idx*2+1, l, mid );
    int rval = constructSTUtil( idx*2+2, mid+1, r );

    ST[idx] = dfsLog_level[lval] < dfsLog_level[rval] ? lval : rval;
    return ST[idx];
}
int getMinST( int idx, int l, int r, int trgL, int trgR )
{
    // In
    if ( trgL <= l && r <= trgR )
        return ST[idx];
    // OutOfRange
    if ( trgR < l || r < trgL )
        return INF;
    
    // Partly In
    int mid = ( r - l ) / 2 + l;
    int lval = getMinST( idx*2+1, l, mid, trgL, trgR );
    int rval = getMinST( idx*2+2, mid+1, r, trgL, trgR );

    if ( lval == INF )
        return rval;
    if ( rval == INF )
        return lval;
    
    return ( dfsLog_level[lval] < dfsLog_level[rval] ? lval : rval );
}