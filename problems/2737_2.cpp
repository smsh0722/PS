#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int T;
int64_t N;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> T;

    for ( int t = 0; t < T; t++ ){
        int64_t ans = 0;

        cin >> N;
        int64_t k = 2;
        while ( 2*k <= (-1+sqrt(1+8*N))){
            int64_t A = 2*N - k*k + k;
            int64_t B = 2 * k;
            if ( A % B == 0 ){
                // l = A / B
                ans++;
            }
            k++;
        }
        cout << ans << "\n";
    }
    
    return 0;
}