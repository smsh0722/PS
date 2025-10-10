/* NOTE: 
처음엔 offline algorithm과 비슷하게 풀려고 하였다.
그러나 결국 O(N^2)인 것은 같기 때문에 의미가 없다.

Naive하게 다시 생각해보면, (i,j)를 모두 조사해야한다.
이때 문제는 더하는 시간이 아니라, (i,j) 쌍 자체가 너무 많다는 것이다. 
쌍을 빠르게 찾으려면, i 가 정해졌을때 j를 정할 수 있으면 좋을 것 같다.
=> map

(0,j)의 누적합을 구한다. (0,i-1) 까지 합을 sum이라고 할 때, prefix[j] - sum = K 인 j를 찾을 수 있으면 좋겠다.
map을 통해 key: prefix[j], value: count를 하여 prefix[j] = K + sum을 만족하는 j의 개수를 빠르게 찾을 수 있겠다.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

// # of elements
int N;
// Target sum
int K;

unordered_map<int,int> m;

vector<int> elements;

int64_t ans = 0;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> K;
    elements.resize(N);
    {
        int sum = 0;
        for ( int ei = 0; ei < N; ei++ ){
            cin >> elements[ei];
            sum += elements[ei];
            
            if ( m.find(sum) == m.end() )
                m[sum] = 1;
            else 
                m[sum]++;
        }
    }

    // DEBUG
    // for ( auto e : m ){
    //     cout << e.first << " " << e.second << endl;
    // }

    int sum = 0;
    for ( int ei = 0; ei < N; ei++ ){
        int trg = K + sum;
        if ( m.find(trg) != m.end() ){
            ans += m[trg];
            // cout << "at ei " << ei << " trg " << trg << " m[trg] " << m[trg] << endl; // DEBUG
        }

        sum += elements[ei];
        m[sum]--;
    }

    cout << ans;

    return 0;
}