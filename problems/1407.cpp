#include <iostream>
#include <vector>

using namespace std;

inline int64_t GetOdd(int64_t l, int64_t r ){
    return ((r+1)/2 - l/2);
}
int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int64_t a, b;
    cin >> a >> b;

    int64_t sum = 0;
    // Cal odd
    sum += GetOdd(a, b);

    // Cal Even
    {
        int64_t divisor = 2;
        while ( divisor <= b && divisor > 0){
            int64_t qMax = b / divisor;
            int64_t qMin = a / divisor;
            if ( a % divisor != 0 )
                qMin++;

            sum += divisor * GetOdd( qMin, qMax );

            divisor = divisor<<1;
        }
    }

    cout << sum;

    return 0;
}