/* NOTE:
나머지 연산 뺄셈 주의
*/
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1000;
const int64_t DIVISOR = 1000000003;

// Size of color book
int N;
// Num of selections
int K;

// combinations[n][r] = nCr
vector<vector<int64_t>> combs( MAX_N+1, vector<int64_t>(MAX_N+1, 1 ) );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;

    for ( int n = 2; n <= MAX_N; n++ ){
        for ( int r = 1; r < n; r++ ){
            combs[n][r] = (combs[n-1][r-1] + combs[n-1][r])%DIVISOR;
        }
    }

    // for ( int n = 1; n <= 20; n++ ){ // DEBUG
    //     for ( int r = 0; r <= n; r++ ){
    //         printf("%dC%d: %d ", n, r, combs[n][r]);
    //     } cout << endl;
    // }

    if ( K == 1 )
        cout << N;
    else {
        int R = N - (2*K - 1);
        if ( R < 0 )
            cout << 0;
        else {
            // NOTE: 나머지 이후 뺄셈이 필요한 경우, 큰수-작은수 일때 음수 나올 수 있음을 주의해서 처리하자.
            cout << (combs[N-K+1][R] + DIVISOR - combs[N-K-1][R]) % DIVISOR;
        }
    }

    return 0;
}