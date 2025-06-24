#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N;

int main(void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;
    
    vector<vector<int>> directedGraph(N);
    vector<int> indegree(N, 0 );
    {
        int a, b;
        for ( int i = 0; i < N; i++ ){
            cin >> a >> b;
            directedGraph[i].push_back(a-1);
            directedGraph[i].push_back(b-1);
            
            indegree[a-1]++;
            indegree[b-1]++;
        }
    }
    
    queue<int> topologicalQ;
    vector<bool> removedNodes(N, false );
    int removedCount = 0;
    for ( int i = 0; i < N; i++ ){
        if ( indegree[i] < 2 ){
            topologicalQ.push(i);
            removedNodes[i] = true;
            removedCount++;
        }
    }
    while ( topologicalQ.empty() == false ){
        int srcNode = topologicalQ.front();
        topologicalQ.pop();

        for ( int i = 0; i < 2; i++ ){
            int trgNode = directedGraph[srcNode][i];
            indegree[trgNode]--;
            if ( indegree[trgNode] < 2 && removedNodes[trgNode] == false ){
                topologicalQ.push(trgNode);
                removedNodes[trgNode] = true;
                removedCount++;
            }
        }
    }

    cout << (N-removedCount);
    if ( removedCount < N ){
        cout << endl;
        for ( int i = 0; i < N; i++ ){
            if ( removedNodes[i] == false )
                cout << i + 1<< " ";
        }
    }
}