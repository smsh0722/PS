/* NOTE:
Naive한 방법은 무엇일까?
고유한 2, 4, 6... 짜리 가로를 시도하고 나머지 길이의 경우의 수를 조사하면 된다.
이때, 나머지 길이에서 계산 반복이 일어난다.
dp로 풀고 싶지만 범위가 문제가 된다.

N의 범위가 엄청 크기 때문에 웬만한 방법으로는 쉽지 않다.

그러나 잘 보면 수식을 세울 수 있고, 행렬을 사용할 수 있다.
이때, 분할 정복을 사용할 수 있다.
*/
#include <iostream>
#include <vector>
using namespace std;

const int64_t DIVISOR = 1000000007;

int64_t N;

vector<vector<int64_t>> mat = {{4,-1},{1,0}};

vector<vector<int64_t>> init= {{3},{1}};

inline int64_t norm( int64_t n )
{
    n %= DIVISOR;
    if( n < 0 ) n += DIVISOR;
    return n;
}
vector<vector<int64_t>> mat_mul( vector<vector<int64_t>>& a, vector<vector<int64_t>>& b )
{
    // lxm dot mxn
    vector<vector<int64_t>> rst(a.size(), vector<int64_t>(b[0].size(), 0) );
    for ( int l = 0; l < a.size(); l++ ){
        for ( int m = 0; m < a[l].size(); m++ ){
            for ( int n = 0; n < b[0].size(); n++ ){
                rst[l][n] += (a[l][m]*b[m][n] + DIVISOR ) % DIVISOR; // NOTE: 음수 MOD 개념
                rst[l][n] = (rst[l][n] + DIVISOR)%DIVISOR;
            }
        }
    }

    return rst;
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    if ( N & 1 ){
        cout << 0;
        return 0;
    }
    else if( N == 2 ){
        cout << 3;
        return 0;
    }

    int64_t k = N/2;
    vector<vector<int64_t>> rst = {{1,0},{0,1}};
    while ( k > 0 ){
        if ( k & 1 ){
            rst = mat_mul(rst, mat);
        }
        mat = mat_mul(mat,mat);
        k >>= 1;
    }

    vector<vector<int64_t>> ans = mat_mul(rst,init);
    cout << ans[1][0];

    return 0;
}