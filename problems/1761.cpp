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
    int nodeNum;
    int dist;
    edge* nextEdge;
};
edge** adjList;


void DFS( bool* visited, int curNode, int* route, int* nodeNumHash, int* distFromRoot, int* count );
int constructSTUtil( int* ST, int idx, int l, int r, int* route, int* nodeNumHash );
int getMinST( int* ST, int idx, int l, int r, int trgL, int trgR );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    int N;
    cin >> N;

    // Input

    adjList = new edge*[N+1];
    {
        for ( int i = 0; i <= N; i++ )
            adjList[i] = nullptr;

        int a, b, c;
        for ( int i = 0; i < N - 1; i++ ){
            cin >> a >> b >> c;
            edge* a2b = new edge{ b, c, adjList[a] };
            edge* b2a = new edge{ a, c, adjList[b] };
            adjList[a] = a2b;
            adjList[b] = b2a;
        }
    }

    // Pre-process

    int* distFromRoot = new int[N+1];
    memset( distFromRoot, 0, sizeof(int)*(N+1) );

    int* nodeNumHash = new int[N+1];
    int* nodeNumHash_reverse = new int[2*N-1];
    int* ST;
    {
        int h = ceil( log2(2*N - 1) );
        int size = (1<<(h+1))-1;
        ST = new int[size];
        
        int* route = new int[2*N-1];
        int count = 0;
        bool* visited = new bool[N+1];
        memset( visited, false, sizeof(bool)*(N+1) );
        DFS( visited, 1, route, nodeNumHash, distFromRoot, &count );

        constructSTUtil( ST, 0, 0, 2*N-1-1, route, nodeNumHash );

        memset( nodeNumHash_reverse, -1, sizeof(int)*(2*N-1));
        for ( int i = 1; i <= N; i++ )
            nodeNumHash_reverse[ nodeNumHash[i] ] = i;
        
        delete[] route;
        delete[] visited;
    }

    // Answer Qeury
    int M;
    cin >> M;
    for ( int i = 0; i < M; i++ ){
        int a, b;
        cin >> a >> b;
        if ( nodeNumHash[a] > nodeNumHash[b] ){
            int tmp = a;
            a = b;
            b = tmp;
        }
        int lca = nodeNumHash_reverse[ getMinST( ST, 0, 0, 2*N-1-1, nodeNumHash[a], nodeNumHash[b] ) ];
        /*
        {// DEbug
        cout << distFromRoot[a] << " + "
             << distFromRoot[b] << " - "
             << "2*" << distFromRoot[lca] << " = ";
        }
        */
        cout << (distFromRoot[a] + distFromRoot[b] - 2*distFromRoot[lca]) << "\n";
    }
    return 0;
}
void DFS( bool* visited, int curNode, int* route, int* nodeNumHash, int* distFromRoot, int* count )
{
    route[*count] = curNode; // Set Route
    nodeNumHash[curNode] = *count; // Set nodeNumHash
    visited[curNode] = true;

    // DFS
    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( visited[curEdge->nodeNum] == true ){
            curEdge = curEdge->nextEdge;
            continue;
        }
        *count += 1;

        distFromRoot[curEdge->nodeNum] = distFromRoot[curNode] + curEdge->dist; // set Dist
        DFS( visited, curEdge->nodeNum, route, nodeNumHash, distFromRoot, count ); // DFS
        route[*count] = curNode;

        curEdge = curEdge->nextEdge;
    }
    (*count)++;
}
int constructSTUtil( int* ST, int idx, int l, int r, int* route, int* nodeNumHash )
{
    // Base Case
    if ( l == r ){
        ST[idx] = nodeNumHash[ route[l] ];
        return ST[idx];
    }
    // Recursive Find
    int mid = ( r - l ) / 2 + l;
    int lval = constructSTUtil( ST, idx*2+1, l, mid, route, nodeNumHash );
    int rval = constructSTUtil( ST, idx*2+2, mid+1, r, route, nodeNumHash );

    ST[idx] = lval < rval ? lval : rval;
    return ST[idx];
}
int getMinST( int* ST, int idx, int l, int r, int trgL, int trgR )
{
    // In
    if ( trgL <= l && r <= trgR )
        return ST[idx];
    // OutOfRange
    if ( trgR < l || r < trgL )
        return INF;
    
    // Partly In
    int mid = ( r - l ) / 2 + l;
    int lval = getMinST( ST, idx*2+1, l, mid, trgL, trgR );
    int rval = getMinST( ST, idx*2+2, mid+1, r, trgL, trgR );

    return ( lval < rval ? lval : rval );
}