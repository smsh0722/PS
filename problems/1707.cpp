/* smsh0722
 * 1707
 * Bipartite Graph
 * */
#include <iostream>
#include <queue>
using namespace std;

struct edge{
    int dst;
    edge* nextEdge;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int K; // # of Test case
    int V, E; // Vertices, Edge
    
    cin >> K;
    for ( int testI = 1; testI <= K; testI++ ){
        cin >> V >> E;

        /* 0 = Non-visited
         * 1 = set-A
         * -1 = set-B
         * */
        int vColor[V+1] = { 0 };

        edge** adjList = new edge*[V+1];
        for ( int i = 0; i <= V; i++ ){
            adjList[i] = nullptr;
        }

        // Input
        int a, b;
        for ( int i = 0; i < E; i++ ){
            cin >> a >> b;
            edge* a2b = new edge;
            {
                a2b->dst = b;
                a2b->nextEdge = adjList[a];
                adjList[a] = a2b;
            }
            edge* b2a = new edge;
            {
                b2a->dst = a;
                b2a->nextEdge = adjList[b];
                adjList[b] = b2a;
            }
        }

        // BFS
        bool ans = true; // Final Answer
        queue<int> Q;   // Queue for BFS
        for ( int i = 1; i <= V; i++ ){
            // Check is visited
            if ( vColor[i] != 0 )
                continue;
            
            // Search Non-visited Vertice
            Q.push( i );
            vColor[i] = {1};
            while ( ans == true && Q.empty() == false ){
                int srcV = Q.front(); Q.pop();
                edge* curEdge = adjList[srcV];
                while ( curEdge != nullptr ){
                    if ( vColor[curEdge->dst] == vColor[srcV] ){ // Both vertices are same set
                        ans = false;
                        break;
                    }
                    else if ( vColor[curEdge->dst] == 0 ){ // Non-visited vertice, assign to diff set
                        Q.push( curEdge->dst );
                        vColor[curEdge->dst] = -vColor[srcV];
                    }

                    curEdge = curEdge->nextEdge;
                }
            }
        }

        // Ans
        if ( ans == true )
            cout << "YES\n";
        else 
            cout << "NO\n";
    
        // Delete to avoid mem leaks
        for ( int i = 1; i <= V; i++ ){
            edge* curEdge = adjList[i];
            edge* nextEdge;
            while( curEdge != nullptr ){
                nextEdge = curEdge->nextEdge;
                delete curEdge;
                curEdge = nextEdge;
            }
        }
    }

    return 0;
}