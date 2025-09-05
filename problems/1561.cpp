/* NOTE: Navie하게 풀어보았지만, 아이디어를 전혀 내지 못했다.

1) Naive하게 풀면 무조건 풀리긴 하지만, 시간 복잡도상 불가능하다.
2) 특정 시간대에 상태는 어떨지 떠올려 보자->parametric_search가 된다.
*/
#include <iostream>
#include <vector>
using namespace std;

const int64_t MAX_N = 2000000000;
const int64_t MAX_M = 10000;

// Num of people
int N;
// Num of rides
int M;

vector<int64_t> times;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    times.resize(M, -1);
    for ( int i = 0; i < M; i++ ){
        cin >> times[i];
    }

    if ( N <= M ){
        cout << N;
        return 0;
    }

    int64_t finTime = -1;
    int64_t l = 1;
    int64_t r = MAX_N * 30;
    while ( l <= r ){
        int64_t mid = ( r - l ) / 2 + l;
        int64_t count = 0;
        for ( int i = 0; i < M; i++ ){
            count += (mid / times[i])+1;
        }

        // cout << "mid: " << mid 
        //     << " count: " << count 
        //     << endl; // DEBUG

        if ( count >= N ){
            finTime = mid;
            r = mid-1;
        }
        else { // count < N
            l = mid+1;
        }
    }

    // cout << "finTime: " << finTime << endl; // DEBUG
    int ans = -1;
    int64_t prevCount = 0;
    for ( int i = 0; i < M; i++ ){
        prevCount += (finTime-1)/times[i] + 1;  
    }
    int64_t leftCount = N - prevCount;
    for ( int i = 0; i < M; i++ ){
        // printf("ride[%d], leftCount: %d\n", i+1, leftCount );//DEBUG
        leftCount -= (finTime/times[i] - (finTime-1)/times[i] );
        if ( leftCount == 0 ){
            ans = i;
            break;
        }
    }
    

    cout << ans + 1;

    return 0;
}