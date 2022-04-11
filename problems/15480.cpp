/* smsh0722
 * 15480
 * LCA와 쿼리
 * */
#include <iostream>
#include <cmath>
#include <cstring>
using namespace std;

const int INF = (-1)^(1<<31);

struct edge{
    int trgNode;
    edge* nextEdge;
};

int* ST;                // store min level node's index
edge** adjList;         // Adjcancy list
int* dfsLog_node;
int* dfsLog_level;
int* firstOccurOfNode;  // first occurence index of each node

void DFS( bool* visited, int curNode, int* count, int curLevel );
int constructSTUtil( int idx, int l, int r );
int getMinLevelIdxST( int idx, int l, int r, int trgL, int trgR );
void getTrgRange( int* trgL, int* trgR, int nodeA, int nodeB );
int selectAns( int lcaList[3] );

int main (void )
{
    ios_base::sync_with_stdio(false);cin.tie(NULL);cout.tie(NULL);

    int N;
    cin >> N;
    // Input
    {
        adjList = new edge*[N+1];
        for ( int i = 0; i <= N; i++ )
            adjList[i] = nullptr;

        int nodeA, nodeB;
        for ( int i = 0; i < N - 1; i++ ){
            cin >> nodeA >> nodeB;
            edge* a2b = new edge{ nodeB, adjList[nodeA] };
            edge* b2a = new edge{ nodeA, adjList[nodeB] };
            adjList[nodeA] = a2b;
            adjList[nodeB] = b2a;
        }
    }

    // Pre-process
    // DFS
    {
        dfsLog_node = new int[2*N-1];
        dfsLog_level = new int[2*N-1];
        firstOccurOfNode = new int[N+1];

        bool* visited = new bool[N+1];
        memset( visited, 0, sizeof(bool)*(N+1) );

        int count = 0;
        DFS( visited, 1, &count, 0 );
        delete[] visited;
    }
    // Construct ST
    {
        int h = ceil( log2(2*N-1) );
        int size = (1<<(h+1)) - 1;
        ST = new int[size];

        constructSTUtil( 0, 0, 2*N-1 -1 );
    }

    // Ans Query
    int M;
    cin >> M;
    {
        int r, u, v;
        int lcaList[3];
        int trgR, trgL;
        for ( int i = 0; i < M; i++ ){
            cin >> r >> u >> v;

            getTrgRange( &trgL, &trgR, r, u );
            lcaList[0] = dfsLog_node[ getMinLevelIdxST( 0, 0, 2*N-1-1, trgL, trgR ) ];
            getTrgRange( &trgL, &trgR, u, v );
            lcaList[1] = dfsLog_node[ getMinLevelIdxST( 0, 0, 2*N-1-1, trgL, trgR ) ];
            getTrgRange( &trgL, &trgR, v, r );
            lcaList[2] = dfsLog_node[ getMinLevelIdxST( 0, 0, 2*N-1-1, trgL, trgR ) ];

            cout << selectAns( lcaList ) << "\n";
        }
    }
}

void DFS( bool* visited, int curNode, int* count, int curLevel )
{
    firstOccurOfNode[curNode] = *count;
    dfsLog_node[*count] = curNode;
    dfsLog_level[*count] = curLevel;
    visited[curNode] = true;
    ++(*count);

    // DFS
    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( visited[curEdge->trgNode] == true ){
            curEdge = curEdge->nextEdge;
            continue;
        }

        DFS( visited, curEdge->trgNode, count, curLevel+1 );
        dfsLog_node[*count] = curNode;
        dfsLog_level[*count] = curLevel;

        ++(*count);
    }
}
int constructSTUtil( int idx, int l, int r )
{
    // Base Case
    if ( l == r ){
        ST[idx] = l;
        return l;
    }

    // Recursively construct
    int mid = ( r - l ) / 2  + l;
    int lval = constructSTUtil( idx*2+1, l, mid );
    int rval = constructSTUtil( idx*2+2, mid+1, r );

    ST[idx] = dfsLog_level[lval] < dfsLog_level[rval] ? lval : rval;
    return ST[idx];
}
int getMinLevelIdxST( int idx, int l, int r, int trgL, int trgR )
{
    // IN 
    if ( trgL <= l && r <= trgR )
        return ST[idx];
    // OutOfRange
    if( trgR < l || r < trgL )
        return INF;
    // Partly In
    int mid = ( r - l ) / 2 + l;
    int lval = getMinLevelIdxST( idx*2+1, l, mid, trgL, trgR );
    int rval = getMinLevelIdxST( idx*2+2, mid+1, r, trgL, trgR );

    if ( lval == INF )
        return rval;
    if ( rval == INF )
        return lval;
    
    return ( dfsLog_level[lval] < dfsLog_level[rval] ? lval : rval );
}
void getTrgRange( int* trgL, int* trgR, int nodeA, int nodeB )
{
    if ( firstOccurOfNode[nodeA] > firstOccurOfNode[nodeB] ){
        int tmp = nodeA;
        nodeA = nodeB;
        nodeB = tmp;
    }
    
    *trgL = firstOccurOfNode[nodeA];
    *trgR = firstOccurOfNode[nodeB];
}
int selectAns( int lcaList[3] )
{
    bool ab = lcaList[0] == lcaList[1];
    bool bc = lcaList[1] == lcaList[2];

    // All equal
    if ( ( ab&bc )== true )
        return lcaList[0];

    // x == y, y != z
    bool ca = lcaList[2] == lcaList[0];
     
    if ( ab == true )
        return lcaList[2];
    else if ( bc == true )
        return lcaList[0];
    else if ( ca == true )
        return lcaList[1];

    return -1; // error
}