/* 1260 DFS n BFS
 * smsh0722
 *
 * */
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

int compare( const int a, const int b )
{
    return a < b;
}
void DFS( const vector<int> edges[], const int V, bool visited[] )
{
    cout << V;
    visited[V] = true;

    for ( int i = 0; i < edges[V].size(); i++ ){
        if ( visited[edges[V][i]] == false ){
            cout << " ";
            DFS( edges, edges[V][i], visited );
        }
    }
}
void BFS( const vector<int> edges[], const int V, bool visited[] )
{
    queue<int> q;
    q.push(V);
    visited[V] = true;
    cout << V;
    while ( q.empty() == false ){
        int src = q.front();
        q.pop();
        for ( int i = 0; i < edges[src].size(); i++ ){
            int dst = edges[src][i];
            if ( visited[dst] == false ){
                visited[dst] = true;
                q.push(dst);
                cout << " " << dst;
            }
        }
    }
}
int main( void )
{
    ios_base::sync_with_stdio(false);
    int N, M, V;
    cin >> N >> M >> V;
    
    vector<int> edges[N+1];
    for ( int i = 0; i < M; i++ ){
        int a, b;
        cin >> a >> b;
        edges[a].push_back(b);
        edges[b].push_back(a);
    }
    /* sort to make ascending list */
    for ( int i = 1; i < N+1; i++ ){
        if ( edges[i].size() > 0 ){
            sort( edges[i].begin(), edges[i].end(), compare );
        }
    }
    /* DFS */
    {
        bool visited[N+1] = {false};
        DFS( edges, V, visited );
    }
    /* BFS */
    {
        cout << "\n";
        bool visited[N+1] = {false};
        BFS( edges, V, visited );
    }

    return 0;
}
