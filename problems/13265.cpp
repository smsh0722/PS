#include <iostream>
#include <vector>
#include <queue>
using namespace std;

enum Color{
    WHITE=-1, RED, BLUE
};

int T;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    for ( int t = 0; t < T; t++ ){
        // # of vertices
        int N;
        // # of edges
        int M;
        
        cin >> N >> M;

        vector<vector<int>> adjList(N+1);
        for ( int mi = 0; mi < M; mi++ ){
            int u, v;
            cin >> u >> v;
            adjList[u].push_back(v);
            adjList[v].push_back(u);
        }

        bool bPossible = true;
        vector<Color> colors(N+1, WHITE);
        for ( int v = 1; v <= N && bPossible; v++ ){
            if ( colors[v] != WHITE)
                continue;
            queue<int> q;
            q.push(v);
            colors[v] = RED;
            while ( q.empty() == false && bPossible ){
                int cur = q.front();
                q.pop();

                for ( auto adj : adjList[cur] ){
                    if ( colors[adj] == WHITE ){
                        q.push(adj);
                        colors[adj] = Color((colors[cur]+1 )% 2);
                    }
                    else if ( colors[adj] == colors[cur] ){
                        bPossible = false;
                        break;
                    }
                }
            }
        }

        if ( bPossible )
            cout << "possible\n";
        else 
            cout << "impossible\n";
    }

    return 0;
}