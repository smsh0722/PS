#include <iostream>
#include <vector>
using namespace std;

int64_t A, B, C;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> A >> B >> C;

    int64_t ans = 1;
    int64_t num = A;
    while ( B > 0 ){
        if ( B & 1 ){
            ans *= num;
            ans %= C;
        }

        num *= num;
        num %= C;
        B >>= 1;
    }

    cout << ans; 

    return 0;
}