#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 2000;

// # of elements
int N;

vector<int> awards(MAX_N, -1);

vector<vector<int>> table( MAX_N, vector<int>(MAX_N, 0 ) );

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int ni = 0; ni < N; ni++ )
        cin >> awards[ni];

    for ( int len = 1; len <= N; len++ ){
        for ( int l = 0; l < N; l++ ){
            int r = l + len - 1;
            if ( r >= N )
                continue;
            int w = N - len + 1;
            if ( len == 1 )
                table[l][r] = max( awards[l]*w, awards[r]*w);
            else {
                table[l][r] = max( 
                    awards[l]*w + table[l+1][r],
                    awards[r]*w + table[l][r-1]
                );
                // cout << "l, r: " << l << " " << r << endl;
                // cout << awards[l]*w << " + " << table[l+1][r] << endl;
                // cout << awards[r]*w << " + " << table[l][r-1] << endl;
            }
            
        }
    }

    // for ( int l = 0; l < N; l++ ){
    //     for ( int r = 0; r < N; r++ ){
    //         cout << table[l][r] << "\t";            
    //     } cout << endl;
    // }
    cout << table[0][N-1];

    return 0;
}