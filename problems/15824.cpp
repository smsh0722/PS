/* NOTE:
최대 최소 쌍을 만들고 그 사이에 있는 x개의 메뉴는 2^x 가지 뽑을 수 있다.
그러나, 최소 최대 쌍을 만드는데 O(N^2)이 걸린다.

Lesson 1)
수식을 전부 나열하다 보면, 규칙이 보인다. 이를 묶어주면 된다.
수식을 통해서 값을 구하는 문제는, ps 알고리즘뿐만 아니라 수식적으로 간단하게 축약할 수 있는지 확인하자.

Lesson 2)
또한 2^x도 나머지를 구해주는 것을 잊지말자.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int64_t DIVISOR = 1000000007;

int N;
int64_t ans = 0;
vector<int64_t> items;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    items.resize(N,-1);
    for ( int i = 0; i < N; i++ ){
        cin >> items[i];
    }

    sort( items.begin(), items.end() );

    int64_t pow2 = 1;
    for ( int i = 0; i < N; i++ ){
        ans += (pow2-1)*( items[i] - items[N-1-i] );
        ans %= DIVISOR;
        pow2 <<= 1;
        pow2 %= DIVISOR;
    }

    cout << ans;

    return 0;
}