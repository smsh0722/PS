#include <iostream>
#include <vector>
using namespace std;

const int MAX_T = 1000;
const int MAX_W = 30;

int T; // time
int W; // move

vector<int> apples;
vector<vector<int>> tableA (MAX_W+1, vector<int>(MAX_T+1, 0)); // Tree 1 [W][T]
vector<vector<int>> tableB (MAX_W+1, vector<int>(MAX_T+1, 0)); // Tree 2 [W][T]

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T >> W;
    apples.resize(T+1);
    for ( int t = 1; t <= T; t++ ){
        cin >> apples[t];
    }

    int w = 0;
    int t = 0;
    for ( t = 1; t <= T; t++ ){
        tableA[w][t] = tableA[w][t-1] + int(apples[t]==1);
    }
    for ( w = 1; w <= W; w++ ){
        for ( t = 1; t <= T; t++ ){
            tableA[w][t] = max(tableA[w][t-1], tableB[w-1][t-1] ) + int(apples[t]==1);
            tableB[w][t] = max( tableB[w][t-1], tableA[w-1][t-1]) + int(apples[t]==2);
        }
    }

    int ans = 0;
    for ( w = 0; w <= W; w++ ){
        ans = max(tableA[w][T], ans );
        ans = max(tableB[w][T], ans );
    }
    cout << ans;
    
    return 0;
}