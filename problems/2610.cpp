#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_INT = ~(1<<31);

struct BFSData{
    int node;
    int dist;
};

struct ParentData{
    int p;
    int time;
};

// {[src][idx]: dst}, src: [1, N]
vector<vector<int>> adjList;
/// {[src]: parentData}, src: [1, N]
vector<ParentData> parents;
// Num of peoples
int N;
// num of connections
int M;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    cin >> M;
    adjList.resize(N+1);
    parents.resize(N+1);
    for ( int i = 1; i<= N; i++ )
        parents[i] = {i, MAX_INT};

    for ( int i = 0; i < M; i++ ){
        int a, b;
        cin >> a >> b;

        adjList[a].push_back(b);
        adjList[b].push_back(a);
    }

    // Test BFS from i
    for ( int i = 1; i <= N; i++ ){
        queue<BFSData> q;
        queue<int> memo;
        vector<bool> visited(N+1, false );
        
        int maxDist = 0;
        q.push({i,0});
        visited[i] = true;
        while ( q.empty() == false ){
            BFSData f = q.front();
            q.pop();
            memo.push(f.node);

            maxDist = maxDist < f.dist ? f.dist : maxDist;
            for ( size_t j = 0; j < adjList[f.node].size(); j++ ){
                int to = adjList[f.node][j];
                if ( visited[to] == true )
                    continue;

                visited[to] = true;
                q.push({to, f.dist+1});
            }
        }
        
        if ( parents[i].time <= maxDist )
            continue;
        
        while (memo.empty() == false ){
            int node = memo.front();
            memo.pop();
            parents[node] = {i, maxDist};
        }
    }

    // Answer
    queue<int> memo;
    for ( int i = 1; i <= N; i++ ){ // Debug
        // printf( "parents[%d] = {p: %d, t:%d}\n", i, parents[i].p, parents[i].time );
        if ( parents[i].p == i ){
            memo.push(i);
        }
    }
    
    cout << memo.size() << endl;;
    while ( memo.empty() == false ){
        int f = memo.front();
        memo.pop();
        cout << f << endl;
    }

    return 0;
}