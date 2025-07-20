/* NOTE:
규칙 찾는게 어려웠다.
Naive하게 펼쳐놓고 천천히 관찰하자.
Binary_search
L, R 어떻게 움직여야할 지 상황에 맞게 논리적으로 잘 세팅하자.
*/
#include <iostream>
#include <vector>
using namespace std;

int64_t N; // NxN array
int64_t k; // b[k];

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> k;

    int64_t l = 1;
    int64_t r = N*N;
    int64_t mid;
    while ( l < r ){
        int64_t sum = 0;
        mid = (r-l)/2+l;
        for ( int i = 1; i <= N; i++ ){
            sum += min((mid/i),N);
        }
        printf("mid %I64d, sum: %I64d\n", mid, sum);
        
        if ( sum < k ){
            l = mid+1;
        }
        else { // sum >= k
            r = mid;
        }
    }
    cout << l;

    return 0;
}