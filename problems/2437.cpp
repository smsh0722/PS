/* NOTE:
아이디어를 떠올리지 못했다.

Naive한 풀이로는 각 추를 포함or미포함을 시켜 2^N가지를 조사하는 방법이다.

여기서 개선하여, 1번 추부터 N번 추까지 순서대로 조사하되,
현재까지의 sum 세트와 Mi 를 합쳐 새로운 sum 세트를 만들고, 다음 무게추로 반복하는 방법을 생각하였다.
그러나 sum set가 최대 1,000,000,000개가 될 수 있어 불가능하다.

다시 생각해보니, 작은 무게추부터 하여 연속적으로 만들 수 있는 합의 최대만 기록하고 있으면 된다.
1~K를 만들 수 있고, Mi = K  + 2 라면 K+2~2k+2를 새로 만들 수 있느데 k+1은 못 만들게 된다.
여기서 멈추면 된다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// # of weights
int N;

vector<int> weights;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    weights.resize(N);
    for ( int ni = 0; ni < N; ni++ )
        cin >> weights[ni];
    
    sort(weights.begin(), weights.end() );

    int maxSum = 0;
    for ( auto w: weights ){
        int nextSum = maxSum + 1;
         if ( nextSum >= w ){
            maxSum += w;
        }
        else {
            break;
        }
    }

    cout << maxSum + 1;

    return 0;
}