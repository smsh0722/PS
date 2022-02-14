#include <iostream>
#include <cstring>
#include <queue>
using namespace std;
int dx[4] = { 0, 0, -1, 1};
int dy[4] = { -1, 1, 0, 0 };

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int w, h; // WxH tile 1~50
    int x, y; // ( x, y )   0~49

    int caseNum; cin >> caseNum;
    int cabageNum;

    for ( int i = 0; i < caseNum; i++ ){ // iterate N case
        cin >> w >> h >> cabageNum;
        
        // Reset: tile[h][w] = tile[y][x]
        bool** tile = new bool* [h];
        for ( int j = 0; j < h; j++ ){
            tile[j] = new bool[w];
            memset( tile[j], false, w );
        }

        /*
        for ( int row = 0; row < h; row++ ){
            for ( int column = 0; column < w; column++ )
                cout << tile[row][column] << " ";
            cout << endl;
        }
        */

        // set cabage position to true
        for ( int j = 0; j < cabageNum; j++ ){
            cin >> x >> y;
            tile[y][x] = true;
        }

        // BFS
        queue<pair<int,int>> color; // pair<int,int>( x, y );
        int result = 0;
        for ( int pY = 0; pY < h; pY++ ){
            for ( int pX = 0; pX < w; pX++ ){
                if ( !tile[pY][pX] ) continue;
                else {
                    color.push( pair<int,int>(pX, pY) );
                    while ( !color.empty() ){
                        int nx, ny;
                        for ( int j = 0; j < 4; j++ ){
                            nx = color.front().first + dx[j];
                            ny = color.front().second + dy[j];
                            if ( nx >= 0 && ny >= 0 && nx < w && ny < h && tile[ny][nx] ){
                                color.push(pair<int,int>( nx, ny ) );
                                tile[ny][nx] = false;
                            }
                        }
                        tile[color.front().second][color.front().first] = false;
                        color.pop();
                    }
                    result++;
                }
            }
        }
        cout << result << "\n";
    }

}