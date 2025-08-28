/* NOTE: GREEDY
큰 걸 제거해야하는 것은 알았다.
하지만 max와 나머지의 관계는 스스로 찾지 못했다.

막대그래프로 상상해보자.
아주 큰 막대그래프가 있다면 전부 이걸 깍아내면 된다.
그러나 막대 높이가 균등한 경우, 하나씩 낮추며 균일하게 깍아간다.
이때, 2개씩 깎기 때문에 총합이 홀수면 1개가 남고, 짝수면 0개가 남는다.

그러나 제한 시간내에 이런 발상은 떠올리지 못할 수 있다.
1) 극단의 케이스(혼자 엄청 큼)
2) 균등한 케이스
두 가지를 관찰하여 규칙을 찾을 수도 있다.
*/
#include <iostream>
#include <queue>
using namespace std;

int N;

int64_t sum = 0;
int64_t maxNum = 0;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    for ( int i = 0; i < N; i++ ){
        int64_t x;
        cin >> x;

        maxNum = maxNum < x ? x : maxNum;
        sum += x;
    }

    // cout << "maxNum: " << maxNum << endl; // DEBUG
    // cout << "sum: " << sum << endl; // DEBUG

    sum -= maxNum;
    if ( maxNum >= sum )
        cout << maxNum - sum;
    else { // maxNum < sum
        if ( (sum+maxNum) % 2 == 0 ){
            cout << 0;
        }
        else {
            cout << 1;
        }
    }

    return 0;
}