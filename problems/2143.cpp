#include <iostream>
#include <map>
#include <vector>

using namespace std;

int T; // Target num
int N, M; // N: num of n(A), M: num of n(B)

vector<int> cumSumA;
vector<int> cumSumB;

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> T;
    cin >> N;
    {
        int num;
        cin >> num;
        cumSumA.push_back(num);
        for ( int i = 1; i < N; i++ ){
            cin >> num;
            cumSumA.push_back(cumSumA[i-1] + num);
        }
    }
    cin >> M;
    {
        int num;
        cin >> num;
        cumSumB.push_back(num);
        for ( int i = 1; i < M; i++ ){
            cin >> num;
            cumSumB.push_back(cumSumB[i-1] + num);
        }
    }

    map<int, int> eventMap; // k: sum, v: count
    {
        for ( int l = -1; l < M; l++ ){
            for ( int r = l+1; r < M; r++ ){
                int sum = cumSumB[r];
                if( l >= 0 )
                    sum -= cumSumB[l];

                if ( eventMap.find(sum) != eventMap.end() )
                    eventMap[sum]++;
                else 
                    eventMap[sum] = 1;
            }
        }
    }

    int64_t count = 0; // NOTE: 각 배열에서 sum 최대 경우의 수 = nC2. 따라서 int 초과 가능.
    for ( int l = -1; l < N; l++ ){
        for ( int r = l+1; r < N; r++ ){
            int aSum = cumSumA[r];
            if( l >= 0 )
                aSum -= cumSumA[l];

            int bSum = T - aSum;
            if( eventMap.find(bSum) != eventMap.end() )
                count += eventMap[bSum];
        }
    }
    cout << count;

    return 0;
}