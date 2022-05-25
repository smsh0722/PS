/* smsh0722
 * 2479
 * 해밍거리
 * */ 
#include <iostream>
#include <string>
#include <cstring>
#include <queue>
#include <stack>
using namespace std;

const int INF = -1^(1<<31);
// # of codes;
int N;
// length of each code
int K;

struct bfs_data{
    int nodeNum;
    int dist;
    string seq;
};

int calHammingDistance( bool** binary_codes, int a, int b );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N >> K;

    bool** binary_codes;
    {
        binary_codes = new bool*[N+1];
        for ( int i = 0; i <= N; i++ )
            binary_codes[i] = new bool[K];
        
        for ( int r = 1; r <= N; r++ ){
            for ( int c = 0; c < K; c++ ){
                char bit;
                cin >> bit;
                binary_codes[r][c] = bit == '1';
            }
        }
    }

    /* Hamming Distance_matrix
     * HD_matrix[r][c] == H(r,c)
     * */
    int** HD_matrix;
    {
        HD_matrix = new int*[N+1];
        for ( int i = 1; i <= N; i++ ){
            HD_matrix[i] = new int[N+1];
            memset( HD_matrix[i], 0, sizeof(int)*(N+1) );
        }
        
        // Calculate Hamming Distance of each pair
        for ( int r = 1; r <= N; r++ ){
            for ( int c = r+1; c <= N; c++ ){
                int HD = calHammingDistance( binary_codes, r, c );
                HD_matrix[r][c] = HD;
                HD_matrix[c][r] = HD;
            }
        }
    }

    string seq;

    int sPoint, ePoint;
    cin >> sPoint >> ePoint;
    /* solve */
    {
        queue<bfs_data> q;
        
        bool* visited;
        {
            visited = new bool[N+1];
            memset( visited, false, N+1 );
        }

        int minHD = INF;
        q.push( bfs_data{sPoint, 0, to_string(sPoint) });
        visited[ sPoint ] = true;
        while ( q.empty() == false && minHD == INF ){
            bfs_data cur_data = q.front();
            q.pop();

            for ( int dst = 1; dst <= N; dst++ ){
                if ( HD_matrix[cur_data.nodeNum][dst] == 1 ){
                    if ( dst == ePoint ){
                        minHD = cur_data.dist + 1;
                        seq = cur_data.seq + to_string(dst);
                        break;
                    }
                    else if ( visited[dst] == false ){
                        q.push( bfs_data{ dst, cur_data.dist+1, cur_data.seq + to_string(dst) } );
                        visited[dst] = true;
                    }
                }
            }
        }

        delete[] visited;
    }
    
    if ( seq.size() == 0 )
        cout << "-1";
    else {
        for ( int i = 0; i < seq.size(); i++ )
            cout << seq.at(i) << " ";
    }

    return 0;
}

int calHammingDistance( bool** binary_codes, int a, int b )
{
    int hd_count = 0;
    for ( int i = 0; i < K; i++ )
        hd_count += binary_codes[a][i] != binary_codes[b][i] ? 1 : 0;
    
    return hd_count;
}