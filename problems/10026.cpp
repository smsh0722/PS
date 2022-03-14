/* smsh0722
 * 10026
 * 적록색약
 * */
#include <iostream>
#include <queue>
using namespace std;

struct pixel{
    int r, c;
};

int main( void )
{
    int N;
    cin >> N;

    /* painting[r][c] 
     * store each pixel's color
     * { R, G, B }
     * */
    char** painting = new char*[N];
    for ( int i = 0; i < N; i++ )
        painting[i] = new char[N];
    
    // Construct Painting
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < N; c++ )
            cin >> painting[r][c];
    }

    int count[2] = {0};
    queue<pixel> Q;
    for( int caseIdx = 0; caseIdx < 2; caseIdx++ ){
        bool** visited = new bool*[N];
        for ( int i = 0; i < N; i++ ){
            visited[i] = new bool[N];
            for ( int j = 0; j < N; j++ )
                visited[i][j] = false;
        }

        // BFS
        for ( int r = 0; r < N; r++ ){
            for ( int c = 0; c < N; c++ ){
                // cout << countI << ": " << r << ", " << c << endl; // Debug

                // Check if visited
                if ( visited[r][c] == true )
                    continue;

                count[caseIdx]++; // Count new set

                Q.push( pixel{ r, c } ); visited[r][c] = true;
                while ( Q.empty() == false ){
                    pixel curPxl = Q.front(); Q.pop();
                    
                    int adjNodes[4][2];
                    adjNodes[0][0] = curPxl.r - 1; adjNodes[0][1] = curPxl.c;
                    adjNodes[1][0] = curPxl.r + 1; adjNodes[1][1] = curPxl.c;
                    adjNodes[2][0] = curPxl.r;     adjNodes[2][1] = curPxl.c - 1;
                    adjNodes[3][0] = curPxl.r;     adjNodes[3][1] = curPxl.c + 1;

                    for ( int i = 0; i < 4; i++ ){
                        if ( adjNodes[i][0] < 0 || adjNodes[i][0] >= N )
                            continue;
                        if ( adjNodes[i][1] < 0 || adjNodes[i][1] >= N )
                            continue;
                        
                        int adjR, adjC;
                        adjR = adjNodes[i][0]; adjC = adjNodes[i][1];
                        if ( visited[adjR][adjC] == true )
                            continue;
                        
                        if ( painting[curPxl.r][curPxl.c] == painting[adjR][adjC] ){
                            Q.push( pixel{ adjR, adjC } ); visited[adjR][adjC] = true;
                        }
                        else if ( caseIdx == 1 ){
                            if ( (painting[curPxl.r][curPxl.c] == 'R' && painting[adjR][adjC] == 'G') 
                                    || (painting[curPxl.r][curPxl.c] == 'G' && painting[adjR][adjC] == 'R' ) ){
                                Q.push( pixel{ adjR, adjC } ); visited[adjR][adjC] = true;
                            }
                        }
                    }
                }
            }
        }

        // Avoid mem leaks
        for ( int i = 0; i < N; i++ )
            delete[] visited[i];
        delete[] visited;
    }

    cout << count[0] << " " << count[1];

    return 0;
}