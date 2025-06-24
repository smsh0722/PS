#include <iostream>
#include <vector>
#include <queue>

using namespace std;

int N, M; // N: num of total people, M: Num of Party

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> M;

    queue<int> truthQ;
    vector<bool> visited(N, false );
    {
        int numOfTruth;
        cin >> numOfTruth;   
        for ( int i = 0; i < numOfTruth; i++ ){
            int node;
            cin >> node;
            node--;
            truthQ.push(node);
            visited[node] = true;
        }
    }

    vector<vector<bool>> adjMat(N, vector<bool>(N, false));
    vector<vector<int>> party(M);
    for ( int partyIdx = 0; partyIdx < M; partyIdx++ ){
        int numOfPeopleInParty;
        cin >> numOfPeopleInParty;

        int node1, node2;
        cin >> node1;
        node1--;
        party[partyIdx].push_back(node1);
        for ( int i = 1; i < numOfPeopleInParty; i++ ){
            cin >> node2;
            node2--;
            party[partyIdx].push_back(node2);
            adjMat[node1][node2] = true;
            adjMat[node2][node1] = true;
        }
    }

    {
        while ( truthQ.empty() == false ){
            int node = truthQ.front();
            truthQ.pop();

            for ( int i = 0; i < N; i++ ){
                if  ( adjMat[node][i] == true && visited[i] == false ){
                    truthQ.push(i);
                    visited[i] = true;
                }
            }
        }
    }

    int count = M;
    for ( int i = 0; i < M; i++ ){
        for ( int j = 0; j < party[i].size(); j++ ){
            if ( visited[party[i][j]] == true ){
                count--;
                break;
            }
        }
    }

    cout << count;
}