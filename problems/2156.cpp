#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_LEN = 200;

// Num of a
int N;
// Num of b
int M;
// Kth Num
int K;

vector<vector<int64_t>> combinations(MAX_LEN+1, vector<int64_t>(MAX_LEN+1, 1));

string BuildNumOfChar( char a, int num)
{
    string s = "";
    for ( int i = 0; i < num; i++ )
        s += a;
    return s;
}

string GetKthStringRecursive( int na, int nb, int k )
{
    // printf("na: %d, nb: %d, k: %d\n", na, nb, k ); //DEBUG
    if ( k == 1) 
        return BuildNumOfChar('a', na) + BuildNumOfChar('z', nb );

    string ans = "";
    int64_t count = 0;
    int64_t prevCount = 0;
    /* L = na+nb
    L-1 L-2 L-3 .. i .. 0
    a   a   a      z ????
    */
    for ( int i = 0; i <= na; i++ ){
        prevCount = count;
        count += combinations[nb+i-1][i];
    
        if ( count >= k ){
            ans += BuildNumOfChar('a', na-i);
            ans += 'z';
            ans += GetKthStringRecursive( i, nb - 1, k - prevCount );
            break;
        }
    }
    
    return ans;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;
    for ( int n = 2; n <= MAX_LEN; n++ ){
        for ( int r = 1; r < n; r++ ){
            combinations[n][r] = combinations[n-1][r-1] + combinations[n-1][r];
        }
    }

    string ans = GetKthStringRecursive(N, M, K);

    if ( ans == "" )
        cout << -1;
    else 
        cout << ans;

    return 0;
}