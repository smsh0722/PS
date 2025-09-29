/* NOTE:
시간 복잡도 상으로 문제가 없으나,
수가 굉장히 커짐.
그러나 나머지 연산을 중간에 함부로 할 수 없기 때문에 옳지 못한 방법.
*/
#include <iostream>
#include <vector>
using namespace std;

int64_t N;

int64_t GCD( int64_t a, int64_t b )
{
    if ( a < b )
        swap(a, b);
    if ( b == 0 )
        return a;
    
    return GCD( b, a%b);
}

int64_t LCM( int64_t a, int64_t b )
{
    int64_t g = GCD( a, b);
    return a / g * b;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    int64_t ans = 1;
    for ( int64_t i = 2; i <= N; i++ ){
        cout << ans << ", " << i << endl;
        if ( ans < 0 ){
            cout << "overflow" << endl;
            return 0;
        }

        ans = LCM(ans, i );
    }   

    cout << ans;
    return 0;
}