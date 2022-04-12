/* smsh0722
 * 3176
 * 도로 네트워크
 * */
#include <iostream>
#include <cmath>
using namespace std;

const int INF = (-1)^(1<<31);

struct edge{
    int trgNode;
    int dist;
    edge* nextEdge;
};
// memo data
struct m_data{
    int min;
    int max;
    int trgNode;
};

edge** adjList; // Adjcancy List
m_data** memo;  // Lifting memo
int* level;     // level of each node

void printMemo( int N, int log);
void DFS( int prevNode, int curNode, int curLevel, int log, int min, int max );
void lca( int nodeA, int nodeB, int log, int* min, int* max );

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
        for ( int i = 0; i < N-1; i++ ){
            cin >> nodeA >> nodeB >> dist;
            edge* a2b = new edge{ nodeB, dist, adjList[nodeA] };
            edge* b2a = new edge{ nodeA, dist, adjList[nodeB] };
            adjList[nodeA] = a2b;
            adjList[nodeB] = b2a;
        }
    }

    int log = ceil( log2(N) );
    // Pre-process
    {
        memo = new m_data*[N+1];
        for ( int i = 0; i <= N; i++ )
            memo[i] = new m_data[log+1]; // idx: 0 ~ log

        level = new int[N+1];

        DFS( 1, 1, 0, log, INF, -INF );
    }
    // Debug
    {
     //   printMemo( N, log );
    }

    // Answer Query
    int K;
    cin >> K;
    {
        int nodeA, nodeB;
        int min, max;
        for ( int i = 0; i < K; i++ ){
            cin >> nodeA >> nodeB;

            min = INF;
            max = -INF;

            lca( nodeA, nodeB, log, &min, &max );
            cout << min << " " << max << "\n";
        }
    }
    return 0;
}

void printMemo( int N, int log)
{
    for ( int i = 0; i < N; i++ ){
        for ( int j = 0; j <= log; j++ ){
            cout << i << "th 2^(" << j << "): " << memo[i][j].min << " " << memo[i][j].max << "\n";
        }
    }
}
void DFS( int prevNode, int curNode, int curLevel, int log, int min, int max )
{
    // Make dp
    memo[curNode][0].trgNode = prevNode;
    memo[curNode][0].max = max;
    memo[curNode][0].min = min;
    for ( int i = 1; i <= log; i++ ){
        memo[curNode][i].trgNode = memo[ memo[curNode][i-1].trgNode ][i-1].trgNode;
        memo[curNode][i].max = memo[curNode][i-1].max > memo[ memo[curNode][i-1].trgNode ][i-1].max ? 
                                    memo[curNode][i-1].max : memo[ memo[curNode][i-1].trgNode ][i-1].max;
        memo[curNode][i].min = memo[curNode][i-1].min < memo[ memo[curNode][i-1].trgNode ][i-1].min ? 
                                    memo[curNode][i-1].min : memo[ memo[curNode][i-1].trgNode ][i-1].min;
    }
    
    // Set level
    level[curNode] = curLevel;

    // DFS
    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( curEdge->trgNode != prevNode ){
            DFS( curNode, curEdge->trgNode, curLevel + 1, log, curEdge->dist, curEdge->dist );
        }
        curEdge = curEdge->nextEdge;
    }
}
void lca( int nodeA, int nodeB, int log, int* min, int* max )
{
    if ( level[nodeA] > level[nodeB] ){
        int tmp = nodeA;
        nodeA = nodeB;
        nodeB = tmp;
    }

    // Lift nodeB
    for ( int i = log; i >= 0; i-- ){
        if ( (level[nodeB] - level[nodeA]) >= (1 << i) ){
            *min = *min < memo[nodeB][i].min ? *min : memo[nodeB][i].min;
            *max = *max > memo[nodeB][i].max ? *max : memo[nodeB][i].max;
            nodeB = memo[nodeB][i].trgNode;
        }
    }
    
    // nodeA is ancestor
    if ( nodeA == nodeB )
        return;

    // Find
    for ( int i = log; i >= 0; i-- ){
        if ( memo[nodeA][i].trgNode != memo[nodeB][i].trgNode ){
            // Find Min
            *min = *min < memo[nodeA][i].min ? *min : memo[nodeA][i].min;
            *min = *min < memo[nodeB][i].min ? *min : memo[nodeB][i].min;
            // Find max
            *max = *max > memo[nodeA][i].max ? *max : memo[nodeA][i].max;
            *max = *max > memo[nodeB][i].max ? *max : memo[nodeB][i].max;
            // Lifting
            nodeA = memo[nodeA][i].trgNode;
            nodeB = memo[nodeB][i].trgNode;
        }
    }
    
    // Find Min
    *min = *min < memo[nodeA][0].min ? *min : memo[nodeA][0].min;
    *min = *min < memo[nodeB][0].min ? *min : memo[nodeB][0].min;
    // Find max
    *max = *max > memo[nodeA][0].max ? *max : memo[nodeA][0].max;
    *max = *max > memo[nodeB][0].max ? *max : memo[nodeB][0].max;
}