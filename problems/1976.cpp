/*
DFS
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_CITY = 200;

int N; // num of city
int M; // num of city to travel

vector<vector<int>> adjList(MAX_CITY);
vector<bool> bVisited(MAX_CITY, false);

void DFS( int n )
{
    if ( bVisited[n] == true )
        return;

    bVisited[n] = true;

    for ( size_t i = 0; i < adjList[n].size(); i++ ){
        DFS(adjList[n][i]);
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    cin >> M;
    for ( int r = 0;  r < N; r++ ){
        for ( int c = 0; c < N; c++ ){
            int in;
            cin >> in;
            if ( in == 1 ){
                adjList[r].push_back(c);
            }
        }
    }

    int c;
    cin >> c;
    DFS(c-1);
    for ( int i = 1; i < M; i++ ){
        cin >> c;
        if ( bVisited[c-1] == false ){
            cout << "NO";
            return 0;
        }
    }
    cout << "YES";

    return 0;
}