#include <iostream>
#include <vector>
using namespace std;

const int64_t MODULO = 1000000007;

int n; // num of buildings
int m; // num of edges
int D;

vector<vector<int64_t>> matrix;
vector<vector<int64_t>> ans;

inline vector<vector<int64_t>> MulMat( const vector<vector<int64_t>>& a, const vector<vector<int64_t>>& b )
{
    vector<vector<int64_t>> rst(n, vector<int64_t>(n,0));

    // mul MxN * NxP = MxP
    for ( int M = 0; M < n; M++ ){
        for ( int N = 0; N < n; N++){
            for ( int P = 0; P < n; P++){
                rst[M][P] += a[M][N] * b[N][P];
                rst[M][P] %= MODULO;
            }
        }
    }

    return rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n >> m;

    // Init
    matrix.resize( n, vector<int64_t>(n, 0));
    ans.resize(n, vector<int64_t>(n, 0));
    for ( int r = 0; r < n; r++ ){
        for ( int c = 0; c < n; c++ ){
            if ( r == c )
                ans[r][c] = 1;
        }
    }

    // Get input
    for ( int i = 0; i < m; i++ ){
        int a, b;
        cin >> a >> b;
        a--;b--;
        matrix[a][b] = 1;
        matrix[b][a] = 1;
    }

    cin >> D;

    while ( D > 0 ){
        if ( (D&1) == 1){
            ans = MulMat(ans, matrix);
        }

        matrix = MulMat(matrix, matrix);
        D = D>>1;
    }

    cout << ans[0][0];

    return 0;
}