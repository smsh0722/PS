/* SOL1)
다양하게 풀 수 있다.

Naive한 풀이를 떠올려보면,

수업 시간을 축으로하여, 각 수업이 진행되는 시간대에 표시하여, 겹치는 수업을 체크하면 된다.
이는 prefix_sum을 사용하여 구할 수 있다.
다만, 수업 시간 범위가 너무 크므로 값 압축을 한번 해주면 된다.

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Class{
    int start, end;
};

const int MAX_COMPRESSED_TIME = 400000;

int N;

vector<Class> classes;
vector<int> compressedTimes;
vector<int> times(MAX_COMPRESSED_TIME+1, 0 );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    classes.resize(N);
    for ( int ni = 0; ni < N; ni++ ){
        int s, e;
        cin >> s >> e;
        classes[ni] = {s,e};
        compressedTimes.push_back(s);
        compressedTimes.push_back(e);
    }

    sort( compressedTimes.begin(), compressedTimes.end() );
    compressedTimes.erase( unique(compressedTimes.begin(), compressedTimes.end()), compressedTimes.end() );

    for ( auto c : classes ){
        int s = lower_bound( compressedTimes.begin(), compressedTimes.end(), c.start ) - compressedTimes.begin();
        int e = lower_bound( compressedTimes.begin(), compressedTimes.end(), c.end ) - compressedTimes.begin();

        times[s] += 1;
        times[e] -= 1;
    }

    int ans = times[0];
    for ( int t = 1; t <= MAX_COMPRESSED_TIME; t++ ){
        times[t] += times[t-1];
        ans = max(times[t], ans );
    }

    cout << ans;

    return 0;
}