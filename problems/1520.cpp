#include <iostream>
#include <vector>
using namespace std;

pair<int, int> moveCase[4] = {
    pair<int, int>(1,0),
    pair<int, int>(-1,0),
    pair<int, int>(0,1),
    pair<int, int>(0,-1)
};

int DFS( const int r, const int c, vector<vector<int>>& map, vector<vector<int>>& dp );

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);
    
    int rSize, cSize;
    cin >> rSize >> cSize;
    vector<vector<int>> map( rSize, vector<int>(cSize) );
    vector<vector<int>> dp( rSize, vector<int>(cSize, -1) );
    for ( int r = 0; r < rSize; r++ ){
        for ( int c = 0; c < cSize; c++ ){
            cin >> map[r][c];
        }
    }

    cout << DFS( 0, 0, map, dp );
    
    return 0;
}

int DFS( const int r, const int c, vector<vector<int>>& map, vector<vector<int>>& dp )
{
    if ( r == ( map.size() - 1 ) && c == ( map[0].size() - 1 ) ){
        return 1;
    }

    if ( dp[r][c] == -1 ){
        int count = 0;
        for ( int i = 0; i < 4; i++ ){
            int trgR = r + moveCase[i].first;
            int trgC = c + moveCase[i].second;
            if ( trgR < map.size() && trgC < map[0].size() ){
                if ( map[trgR][trgC] < map[r][c] ){
                    count += DFS( trgR, trgC, map, dp );
                }
            }
        }

        dp[r][c] = count;
    }

    return dp[r][c];
}
