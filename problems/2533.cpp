#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1000000;

int N;
int ans = 0;

vector<vector<int>> adjList(MAX_N);
vector<bool> visited(MAX_N+1, false);

bool GetMinAliadapterRecursive( int node )
{
    visited[node] = true;
    
    bool bAliadapter = false;
    for ( size_t i = 0; i < adjList[node].size(); i++ ){
        if ( visited[adjList[node][i]] == true )
            continue;
        bool bChildAliadapter = GetMinAliadapterRecursive( adjList[node][i] );
        if ( bChildAliadapter == false )
            bAliadapter = true;
    }

    if ( bAliadapter == true )
        ans++;
    return bAliadapter;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    
    for ( int i = 0; i < N-1; i++ ){
        int src, dst;
        cin >> src >> dst;
        adjList[dst].push_back(src);
        adjList[src].push_back(dst);
    }

    GetMinAliadapterRecursive(1);
    cout << ans;

    return 0;
}