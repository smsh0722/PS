/* smsh0722
 * 1707
 * Bipartite Graph
 * */
#include <iostream>
#include <queue>
using namespace std;

struct node{
    int dst;
    node* nextNode;
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

        /* Adjacency List
         * src[dst] = src to dst
         * */
        node** src = new node*[V+1];
        for ( int i = 0; i <= V; i++ ){
            src[i] = nullptr;
        }

        // Input
        int a, b;
        for ( int i = 0; i < E; i++ ){
            cin >> a >> b;
            node* a2b = new node;
            {
                a2b->dst = b;
                a2b->nextNode = src[a];
                src[a] = a2b;
            }
            node* b2a = new node;
            {
                b2a->dst = a;
                b2a->nextNode = src[b];
                src[b] = b2a;
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
                node* curEdge = src[srcV];
                while ( curEdge != nullptr ){
                    if ( vColor[curEdge->dst] == vColor[srcV] ){ // Both vertices are same set
                        ans = false;
                        break;
                    }
                    else if ( vColor[curEdge->dst] == 0 ){ // Both vertices are diff sets
                        Q.push( curEdge->dst );
                        vColor[curEdge->dst] = -vColor[srcV];
                    }

                    curEdge =  curEdge->nextNode;
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
            node* curNode = src[i];
            node* nextNode;
            while( curNode != nullptr ){
                nextNode = curNode->nextNode;
                delete curNode;
                curNode = nextNode;
            }
        }
    }

    return 0;
}