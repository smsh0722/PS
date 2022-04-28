/* smsh0722
 * 1506
 * 경찰서
 * */
#include <iostream>
#include <stack>
#include <queue>
#include <cstring>
using namespace std;

const int INF = (-1)^(1<<31);
int N;

void topological_sort( stack<int>& topological_order, bool** adjMatrix, bool* visited, int curNode );
void getSCC( queue<int>& scc, bool** adjMatrix, bool* visited, int curNode );
int getMinCost( queue<int>& scc, int* cost );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;

    int* cost;
    // Input Cost
    {
        cost = new int[N];
        
        for ( int i = 0; i < N; i++ )
            cin >> cost[i];
    }

    bool** adjMatrix;
    // Input adjacency matrix
    {
        adjMatrix = new bool*[N];
        for ( int i = 0; i < N; i++ )
            adjMatrix[i] = new bool[N];

        char e;
        for ( int r = 0; r < N; r++ ){
            for ( int c = 0; c < N; c++ ){
                cin >> e;
                adjMatrix[r][c] = e == '1';
            }
        }
    }

    stack<int> topological_order;
    // Get topological order
    {
        bool* visited = new bool[N];
        memset( visited, false, sizeof(bool)*N );

        for ( int i = 0 ; i < N; i++ ){
            if ( visited[i]  == false )
                topological_sort( topological_order, adjMatrix, visited, i );
        }

        delete[] visited;
    }

    
    bool** adjMatrix_reverse;
    // Construct adjMatrix reverse
    {
        adjMatrix_reverse = new bool*[N];
        for ( int i = 0; i < N; i++ )
            adjMatrix_reverse[i] = new bool[N];
        
        for ( int r = 0; r < N; r++ ){
            for ( int c = 0; c < N; c++ ){
                adjMatrix_reverse[c][r] = adjMatrix[r][c];
            }
        }
    }
    
    int cost_sum = 0;
    // Solve
    {
        bool* visited = new bool[N];
        memset( visited, false, sizeof(bool)*N );

        while ( topological_order.empty() == false ){
            int curNode = topological_order.top();
            topological_order.pop();

            if ( visited[curNode] == false ){
                queue<int> scc;
                getSCC( scc, adjMatrix_reverse, visited, curNode );   
                cost_sum += getMinCost( scc, cost );
            }
        }

        delete[] visited;
    }

    // Print Answer
    cout << cost_sum;
    
    return 0;
}

void topological_sort( stack<int>& topological_order, bool** adjMatrix, bool* visited, int curNode )
{
    visited[curNode] = true;
    for ( int i = 0; i < N; i++ ){
        if ( adjMatrix[curNode][i] == true && visited[i] == false )
            topological_sort( topological_order, adjMatrix, visited, i );
    }

    topological_order.push(curNode);
}
void getSCC( queue<int>& scc, bool** adjMatrix, bool* visited, int curNode )
{
    visited[curNode] = true;
    
    scc.push(curNode);

    for ( int i = 0; i < N; i++ ){
        if ( adjMatrix[curNode][i] == true && visited[i] == false )
            getSCC( scc, adjMatrix, visited, i );
    }
}
int getMinCost( queue<int>& scc, int* cost )
{
    int min = INF;
    while ( scc.empty() == false ){
        int curNode = scc.front();
        scc.pop();

        min = min < cost[curNode] ? min : cost[curNode];
    }

    return min;
}