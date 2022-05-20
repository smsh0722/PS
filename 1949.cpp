/* smsh0722
 * 1949
 * 우수 마을
 * */
#include <iostream>
using namespace std;

int N;

struct edge{
    int dst;
    edge* nextEdge;
};

struct dp_data{
    int include;
    int exclude;
};

void constructDP( dp_data* dp, edge** adjList, int* numOfInhabitants, int pNode, int curNode );

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N;
    
    int* numOfInhabitants;
    {
        numOfInhabitants = new int[N+1];
        numOfInhabitants[0] = 0;
        for ( int i = 1; i <= N; i++ )
            cin >> numOfInhabitants[i];
    }

    edge** adjList;
    {
        adjList = new edge*[N+1];
        for ( int i = 0; i <= N; i++ )
            adjList[i] = nullptr;

        for ( int i = 0; i < N-1; i++ ){
            int a, b;
            cin >> a >> b;
            
            edge* a2b = new edge{ b, adjList[a] };
            adjList[a] = a2b;

            edge* b2a = new edge{ a, adjList[b] };
            adjList[b] = b2a;
        }    
    }

    dp_data* dp;
    // Solve
    {
        dp = new dp_data[N+1];
        for ( int i = 0; i <= N; i++ ){
            dp[i].include = 0;
            dp[i].exclude = 0;
        }

        constructDP( dp, adjList, numOfInhabitants, 1, 1 );
    }

    cout << ( dp[1].include > dp[1].exclude ? dp[1].include : dp[1].exclude );

    return 0;
}

void constructDP( dp_data* dp, edge** adjList, int* numOfInhabitants, int pNode, int curNode )
{
    dp[curNode].include += numOfInhabitants[curNode];
    // dp[curNode].exclude += 0;

    edge* curEdge = adjList[curNode];
    while ( curEdge != nullptr ){
        if ( curEdge->dst != pNode ){
            constructDP( dp, adjList, numOfInhabitants, curNode, curEdge->dst );
            dp[curNode].include += dp[curEdge->dst].exclude;
            dp[curNode].exclude += dp[curEdge->dst].include > dp[curEdge->dst].exclude ?
                                    dp[curEdge->dst].include : dp[curEdge->dst].exclude;
        }
        curEdge = curEdge->nextEdge;
    }
}