#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int main( void )
{
    int comN, netN;
    cin >> comN >> netN;

    // Initialize Graph
    bool** graph = new bool* [comN+1]; // 0 ~ comN
    for ( int i = 0; i <= comN; i++ ){
        graph[i] = new bool[comN+1];
        memset( graph[i], false, comN+1 );
    }
    // Set Graph
    int a, b;
    for ( int i = 0 ; i < netN; i++ ){
        cin >> a >> b;
        graph[a][b] = true;
        graph[b][a] = true;
    }

    /*
    for ( int i = 0; i <= comN; i++ ){
        for ( int j = 0; j <= comN; j++ ){
            cout << graph[i][j] << " ";
        }
        cout << endl;
    }
    */

    // BFS
    bool* V = new bool[comN+1]; // 0~comN
    memset( V, false, comN + 1 );
    queue<int> color;
    color.push(1);
    while ( !color.empty() ){
        for ( int i = 1; i <= comN; i++ ){
            if ( graph[color.front()][i] ){
                if( !V[i] ) color.push(i);
            }
        }
        V[color.front()] = true;
        color.pop();
    }

    //print
    int count = 0;
    for ( int i = 0; i <= comN; i++ ){
        if ( V[i] ) {
            count++;
            // cout << i << " "; //Debug;
        }
    }
    cout << count - 1 << endl;
}