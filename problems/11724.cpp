#include <iostream>
#include <cstring>
#include <queue>
using namespace std;

int main( void )
{
    int vNum, eNum; // vertice, Edge
    cin >> vNum >> eNum;

    // initialize graph
    bool** graph = new bool* [vNum + 1]; // 0, 1 ~ vNum
    for ( int i = 0; i <= vNum; i++ ){
        graph[i] = new bool[vNum+1];
        memset( graph[i], false, vNum + 1 );
    }
    
    // set edge
    int a, b;
    for ( int i = 0; i < eNum; i++ ){
        cin >> a >> b;
        graph[a][b] = true;
        graph[b][a] = true;
    }

    // BFS
    int result = 0;
    bool* visited = new bool[vNum + 1];
    memset( visited, false, vNum + 1 );

    for ( int row = 1; row <= vNum; row++ ){
        queue<int> q;
        bool counter = false;
        if ( visited[row] ) continue;

        for ( int column = 1; column <= vNum; column++ ){
            if ( graph[row][column] == true && visited[column] == false ){
                if ( q.empty() ){
                    q.push( row );
                    visited[row] = true;
                }
                q.push( column );
                visited[column] = true;
                counter = true;
                //cout << row << "-" << column << endl; // Debug
            }
        }
        if ( counter ){
            result++;
            q.pop();
        }
        while ( !q.empty() ){
            for ( int i = 1; i <= vNum; i++ ){
                if( graph[q.front()][i] == true && visited[i] == false ){
                    q.push( i );
                    visited[i] = true;
                    //cout << q.front() << "-" << i << endl; // Debug
                }
            }
            q.pop();
        }
    }

    for ( int i = 1; i <= vNum; i++ )
        if ( visited[i] == false ) result++;

    cout << result << endl;
    return 0;
}