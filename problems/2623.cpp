#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_N = 1000;

int N; // num of singers
int M; // num of PD

vector<int> indegree(MAX_N+1, 0);
vector<vector<int>> adjList(MAX_N+1);
vector<bool> visited(MAX_N+1, false);
queue<int> q;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for( int m = 0; m < M; m++ ){
        int num = 0;
        cin >> num;
        
        int singer = 0;
        cin >> singer;
        for( int n = 1; n < num; n++ ){
            int nextSinger=0;
            cin >> nextSinger;
            adjList[singer].push_back(nextSinger);
            indegree[nextSinger]++;
            singer = nextSinger;
        }
    }

    for( int i = 1; i <= N; i++ ){
        if( indegree[i] == 0 )
            q.push(i);
    }

    int count = 0;
    vector<int> ans;
    while ( q.empty() == false ){
        int singer = q.front();
        q.pop();

        if( visited[singer] == true )
            continue;
        visited[singer] = true;
        count++;
        ans.push_back(singer);

        for ( size_t i = 0; i < adjList[singer].size(); i++ ){
            int next = adjList[singer][i];
            indegree[next]--;
            if ( indegree[next] == 0){
                q.push(next);
            }
        }
    }

    if ( count == N ){
        for ( int i = 0; i < N; i++ )
            cout << ans[i] << "\n";
    }
    else {
        cout << 0;
    }
    
    return 0;
}