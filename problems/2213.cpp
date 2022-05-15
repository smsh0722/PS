/* smsh0722
 * 2213
 * 트리의 독립집합
 * */
#include <iostream>
#include <queue>
using namespace std;

struct edge{
    int dst;
    edge* nextEdge;
};

struct dp_data{
    int include_val;
    int exclude_val;
};

int N;

void constructDP( int* weights, edge** adjList, dp_data* dp, int curNode, int pNode );
void traceDP( edge** adjList, dp_data* dp, int curNode, int pNode, bool isCurIncluded, priority_queue<int>& sets );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;

    int* weights;
    {
        weights = new int[N+1];
        for ( int i = 1; i <= N; i++ )
            cin >> weights[i];
    }

    edge** adjList;
    {
        adjList = new edge*[N+1];
        for ( int i = 0; i <= N; i++ )
            adjList[i] = nullptr;
        
        int a, b;
        for ( int i = 0; i < N-1; i++ ){
            cin >> a >> b;
            
            edge* a2b = new edge{ b, adjList[a] };
            adjList[a] = a2b;

            edge* b2a = new edge{ a, adjList[b] };
            adjList[b] = b2a;
        }
    }

    dp_data* dp;
    {
        dp = new dp_data[N+1];
        for ( int i = 0; i <= N; i++ ){
            dp[i].exclude_val = 0;
            dp[i].include_val = 0;
        }
    }

    // Solve
    {    
        constructDP( weights, adjList, dp, 1, 0 );
        
        bool isRootIncluded = dp[1].include_val > dp[1].exclude_val;

        priority_queue<int> sets;
        traceDP( adjList, dp, 1, 0, isRootIncluded, sets );
        
        // Print max
        cout << ( isRootIncluded == true ? dp[1].include_val : dp[1].exclude_val ) << "\n";

        // Print seq
        while ( sets.empty() == false ){
            int node = -sets.top();
            sets.pop();
            cout << node << " ";
        }
    }
    
    return 0;
}

void constructDP( int* weights, edge** adjList, dp_data* dp, int curNode, int pNode )
{
    // Add weight of current node
    dp[curNode].include_val += weights[curNode];
    dp[curNode].exclude_val += 0;

    // DFS
    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( curEdge->dst != pNode ){
            constructDP( weights, adjList, dp, curEdge->dst, curNode );
            dp[curNode].include_val += dp[curEdge->dst].exclude_val;
            dp[curNode].exclude_val += dp[curEdge->dst].include_val > dp[curEdge->dst].exclude_val ?
                                        dp[curEdge->dst].include_val : dp[curEdge->dst].exclude_val;
        }
        curEdge = curEdge->nextEdge;
    }
}

void traceDP( edge** adjList, dp_data* dp, int curNode, int pNode, bool isCurIncluded, priority_queue<int>& sets )
{
    if ( isCurIncluded == true )
        sets.push( -curNode );
    
    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( curEdge->dst != pNode ){
            if ( isCurIncluded == true )
                traceDP( adjList, dp, curEdge->dst, curNode, false, sets );
            else {// IsCurIncluded == false 
                int isTrgIncluded = dp[curEdge->dst].include_val > dp[curEdge->dst].exclude_val;
                traceDP( adjList, dp, curEdge->dst, curNode, isTrgIncluded, sets );
            }
        }
        curEdge = curEdge->nextEdge;
    }
}