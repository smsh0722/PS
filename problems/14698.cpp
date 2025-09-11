/* NOTE:
나머지 연산 타이밍이 중요했다.

1. 새로운 슬라임은 modulo 연산을 하지 않는다.
2. 에너지 누적 곱만 modulo를 하면 되는데, modulo 를 마지막에만 하는게 아니라 연산 과정에서 해줘야한다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

const int DIVISOR = 1000000007;
const int MAX_BIGINT_LEN = 37;

int T;
int N;

struct CompareEnergy{
    bool operator()( const int64_t a, const int64_t b )
    {
        return a > b;
    }
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for ( int t = 0; t < T; t++ ){
        cin >> N;
        
        priority_queue<int64_t, vector<int64_t>, CompareEnergy> pq;
        vector<int64_t> stages(N-1);
        for ( int i = 0; i < N; i++ ){
            int64_t e;
            cin >> e;
            pq.push(e);
        }
        
        int stageI = 0;
        while ( pq.size() > 1 )
        {
            int64_t e1 = pq.top(); pq.pop();
            int64_t e2 = pq.top(); pq.pop();
            int64_t newEnergy = e1*e2;

            pq.push( newEnergy );
            stages[stageI++] = newEnergy;
        }

        int64_t energySum = 1;
        for ( int i = 0; i < N -1 ;i++ ){
            energySum = energySum*(stages[i]%DIVISOR)%DIVISOR;
        }

        cout << energySum << "\n";
    }
    
    return 0;
}