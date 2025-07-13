/* NOTE:
1. prefix sum을 사용하여 O(N)으로 합하는 것을 생각하지 못했다.
2. 끝나는 시간 계산에 익숙해지자.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <algorithm>

using namespace std;

struct Time{
    int s;
    int e;
};

struct OrderByTimeEAsc {
    bool operator()( const Time& a, const Time& b )
    {
        return a.e > b.e; // e 오름차순
    }
};
bool OrderByTimeSAsc( const Time& a, const Time& b ){
    return a.s < b.s; // s 오름차순
}

const int MAX_TIME_PRESSED = 2000000;

priority_queue<Time, vector<Time>, OrderByTimeEAsc> pq;
vector<Time> mosquitos;
vector<int> times;
vector<int> prefixSum;

int N;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int i = 0; i < N; i++ ){
        Time t;
        cin >> t.s >> t.e;
        mosquitos.push_back(t);
        times.push_back(t.s);
        times.push_back(t.e);
    }

    sort(mosquitos.begin(), mosquitos.end(), OrderByTimeSAsc);
    
    sort(times.begin(), times.end() );
    times.erase(unique(times.begin(), times.end()), times.end());

    prefixSum.resize(MAX_TIME_PRESSED+1, 0);
    for ( int mi = 0; mi < N; mi++ ){
        Time m = mosquitos[mi];
        m.s = lower_bound(times.begin(), times.end(), m.s ) - times.begin();
        m.e = lower_bound(times.begin(), times.end(), m.e ) - times.begin();
        prefixSum[m.s] += 1;
        prefixSum[m.e] -= 1;
    }

    int max = prefixSum[0];
    for ( size_t i = 1; i < times.size(); i++ ){
        prefixSum[i] = prefixSum[i] + prefixSum[i-1];
        max = prefixSum[i] > max ? prefixSum[i] : max;
    }

    /*
    for ( size_t i = 0; i < times.size(); i++ ){
        printf( "[%d]: t:%d, c:%d\n", i, times[i], prefixSum[i]);
    }*/

    Time maxTime = {-1,-1};
    {
        for ( size_t ti = 0; ti < prefixSum.size(); ti++ ){
            if ( max == prefixSum[ti] && maxTime.s == -1){
                maxTime.s = times[ti];
            }
            maxTime.e = times[ti];
            
            if ( maxTime.s != -1 && max != prefixSum[ti] )
                break;
        }
    }
    cout << max << "\n";
    cout << maxTime.s << " " << maxTime.e;
    return 0;
}