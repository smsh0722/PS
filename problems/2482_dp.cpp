#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1000;
const int64_t DIVISOR = 1000000003;

// Size of color book
int N;
// Num of selections
int K;

// dpTable[color][count][cur select][end select]
int64_t dpTable[MAX_N+1][MAX_N+1][2][2] = {0};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> K;

    if ( K > (N/2) ){
        cout << 0;
        return 0;
    }

    dpTable[1][1][true][true] = 1;
    dpTable[1][0][false][false] = 1;
    for ( int color = 2; color <= N; color++ ){
        for ( int count = 0; count <= (N/2); count++ ){
            dpTable[color][count][false][false] = (dpTable[color-1][count][true][false] 
                                                + dpTable[color-1][count][false][false]) % DIVISOR;

            dpTable[color][count][true][false] = dpTable[color-1][count-1][false][false];
            
            dpTable[color][count][false][true] = (dpTable[color-1][count][true][true] 
                                                + dpTable[color-1][count][false][true]) % DIVISOR;
            dpTable[color][count][true][true] = dpTable[color-1][count-1][false][true];
        }
    }

    int64_t rst = (dpTable[N][K][true][false] + dpTable[N][K][false][true]) % DIVISOR;
    rst = ( rst + dpTable[N][K][false][false] ) % DIVISOR;
    cout << rst;

    return 0;
}