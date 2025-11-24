/* NOTE:
브루트포스밖에 없는 것은 깨달았다.
P > Q 로 두고 모든 x로 P*x를 시도하였다.
그러나, 0.5초 내로 풀기엔 시간 복잡도가 너무 크다.
어떻게 단축할 수 있을까?

잘 생각해보면 x가 Q보다 커지면
P*x+Q*y
=P*(Q+x')+Q*y
=P*x'+Q*(P+y)
가 된다.
따라서, x를 무한정 늘리는 게 아니라, P*x가 D보다 작으면서, x가 Q보다도 작은 범위만 시도하면 된다.
*/
#include <iostream>

using namespace std;

int64_t D;
int64_t P, Q;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> D;
    {
        int a, b;
        cin >> a >> b;
        P = max(a,b);
        Q = min(a,b);
    }

    int64_t ans = INT32_MAX;
    for ( int64_t x = 0; x <= min(D/P+1, Q); x++ ){
        int64_t PX = P*x;
        int64_t left = D - PX;
        int64_t localAns = PX;
        if ( left > 0){
            localAns += left%Q == 0 ? 0 : Q;
            localAns += (left/Q) * Q;
        }
        
        // cout << "x: " << x << endl; // DEBUG
        ans = min(ans, localAns);
    }

    cout << ans;

    return 0;
}