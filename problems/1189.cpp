#include <iostream>
#include <vector>

using namespace std;

int R, C, K;
int pathNum = 0;

void FindPath( vector<vector<char>>& roadMat, vector<vector<bool>>& visited, int r, int c, int depth = 1);

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> R >> C >> K;

    vector<vector<char>> roadMat(R, vector<char>(C));
    vector<vector<bool>> visited(R, vector<bool>(C, false));
    for ( int r = 0; r < R; r++ ){
        for ( int c = 0; c < C; c++ ){
            cin >> roadMat[r][c];
        }
    }

    FindPath(roadMat, visited, R-1, 0);

    cout << pathNum;
}

void FindPath( vector<vector<char>>& roadMat, vector<vector<bool>>& visited, int r, int c, int depth)
{
    // Check wrong 
    if ( r < 0 || r >= R )
        return;
    if ( c < 0 || c >= C )
        return;
    if ( depth > K )
        return;
    if ( roadMat[r][c] == 'T' )
        return;
    if ( visited[r][c] == true )
        return;
    // Check correct
    if ( r == 0 && c == (C-1) && depth == K){
        pathNum++;
        return;
    }
    
    // find more depth
    visited[r][c] = true;
    FindPath( roadMat, visited, r-1, c, depth+1 );
    FindPath( roadMat, visited, r, c-1, depth+1 );
    FindPath( roadMat, visited, r, c+1, depth+1);
    FindPath( roadMat, visited, r+1, c, depth+1);
    visited[r][c] = false;
}
