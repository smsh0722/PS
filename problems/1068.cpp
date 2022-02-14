#include <iostream>
#include <vector>
using namespace std;

int DFS( const int curr, const vector<vector<int>>& adjList );

int main( void )
{
    int n; cin >> n;
    int trg;
    
    vector<vector<int>> adjList(n);
    int root;
    {
        vector<int> parent(n);
        int p;
        for ( int c = 0; c < n; c++ ){
            cin >> p;
            if ( p == -1 ){
                root = c;
            }
            else {
                parent[c] = p;
                adjList[p].push_back(c);
            }
        }
        cin >> trg;
        {
            adjList[trg].clear();
            vector<int>& anAdjList = adjList[parent[trg]];
            for ( int i = 0; i < anAdjList.size(); i++ ){
                if ( anAdjList[i] == trg ){
                    anAdjList.erase( anAdjList.begin() + i );
                    break;
                }
            }
        }
    }

    if ( root == trg ) {
        cout << 0;
    }
    else {
        cout << DFS( root, adjList );
    }
}

int DFS( const int curr, const vector<vector<int>>& adjList )
{   
    if( adjList[curr].size() == 0 ){
        return 1;
    }
    else {
        int count = 0;
        for ( int i = 0; i < adjList[curr].size(); i++ ){
            count += DFS( adjList[curr][i], adjList );
        }
        return count;
    }
}