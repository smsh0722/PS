/* NOTE:
map의 O(logN)보다 unordered_map의 O(1)이 빨라 undordered_map을 썻다.
그러나, unordered_map같은 경우에도, collision이 많은 경우 O(1)보다 느려질 수 있다.
충돌이 많이 생길 가능성이 존재하다면 사용하지 말자.

또한 map의 operator[]도 디테일하게 알아두자.
*/
#include <iostream>
#include <vector>
#include <unordered_map>

using namespace std;

const int MAX_N = 4000;
const int NUM_OF_ARR = 4;

int N;
vector<vector<int>> arr(NUM_OF_ARR, vector<int>(MAX_N,0)); // [arr:a,b,c,d][idx]
unordered_map<int, int> m; // key: sum, val: count;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); 

    cin >> N;
    for ( int i = 0; i < N; i++ ){
        cin >> arr[0][i]
            >> arr[1][i]
            >> arr[2][i]
            >> arr[3][i];
    }

    for ( int ci = 0; ci < N; ci++ ){
        for ( int di = 0; di < N; di++ ){
            m[arr[2][ci] + arr[3][di]]++;
        }
    }

    int64_t ans = 0;
    for ( int ai = 0; ai < N; ai++ ){
        for ( int bi = 0; bi < N; bi++ ){
            int trg = -(arr[0][ai] + arr[1][bi]);
            if ( m.find(trg) != m.end() )
                ans += m[trg];
        }
    }

    cout << ans;

    return 0;
}