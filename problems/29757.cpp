#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 70000;
const int MAX_L = 5;

int T;
// [num N][num L]: [0,70000]x[0,4]
vector<vector<int>> table (MAX_N+1, vector<int>(MAX_L,0));

int main (void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Build Table
    table[1][0] = 1;
    for ( int c = 1; c < MAX_L; c++ ){
        int prevRoot = 0;
        for ( int r = 1; r <= MAX_N; r++ ){
            int newRoot = prevRoot+1;
            if ( r > newRoot*newRoot ){
                table[r][c] = table[r-1][c] + table[newRoot][c-1];
                prevRoot = newRoot;
            }
            else {
                table[r][c] =  table[r-1][c];
            }
        }
    }

    // Ans
    cin >> T;
    for ( int t = 0; t < T; t++ ){
        int n, l;
        cin >> n >> l;

        if ( l > 5 )
            cout << 0 << "\n";
        else 
            cout << table[n][l-1] << "\n";
    }

    return 0;
}