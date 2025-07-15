#include <iostream>
#include <vector>
#include <cmath>
#include <map>
using namespace std;

int64_t N, P, Q, X, Y;

map<int64_t, int64_t> m;

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
    /* NOTE: 
        m.insert() 보다 m[] 이 더 빠르다.

        아래 코드가 살짝 더 느리다.(But, 디버그엔 더 편하므로 ps에서만 위에처럼 하자.)
        int64_t rst = GetAiRecursive(l) + GetAiRecursive(r);
        m[i] = rst;

        return rst;
    */
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> P >> Q >> X >> Y;

    cout << GetAiRecursive(N);

    return 0;
}