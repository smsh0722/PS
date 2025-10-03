#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int64_t L, U;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> L >> U;
    int64_t rst = 0;

    int64_t diff = U - L + 1;
    int64_t divisor = 1;
    while ( divisor <= U ){
        int64_t num = diff/divisor;
        num += diff%divisor == 0? 0 : 1;
        num = max( num, int64_t(10)     );

        int s = L % divisor;
        s = L - s;
        int e = U % divisor;
        e = divisor - e;
        e = U + e;

        int fNum = (L / divisor)%10;

        int64_t sum = 0;
        int i = 0;
        for ( ; i < num; i++ ){
            sum += (fNum+ i)%10;
        }
        

        divisor *= 10;
    }
    
    cout << rst;

    return 0;
}