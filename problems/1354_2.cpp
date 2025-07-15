/* NOTE: map vs unordered_map
key 값 순서대로 접근할 필요가 없는 경우엔 unordered_map 쓰자.
hash table을 사용하여 O(1)으로 매우 빠르다.
*/

#include <iostream>
#include <vector>
#include <cmath>
#include <unordered_map>
using namespace std;

int64_t N, P, Q, X, Y;

unordered_map<int64_t, int64_t> m;

int64_t GetAiRecursive( int64_t i )
{
    if ( i <= 0 )
        return 1;

    if ( m.find(i) != m.end() )
        return m[i];

    // i > 0 && first time 
    int64_t l = i/P - X;
    int64_t r = i/Q - Y;
    return (m[i] = GetAiRecursive(l) + GetAiRecursive(r));
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> P >> Q >> X >> Y;

    cout << GetAiRecursive(N);

    return 0;
}