/*
app1~N 까지 넣을까 말까로 분할 정복
DP가능-> BUT 메모리를 축으로 하기엔 메모리 초과 가능
맵+메모이제이션으로 필요한 것만 저장하려고 했으나 역시 메모리 초과.
대신, cost를 축으로 knapsack으로 가능.
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 100;
const int MAX_COST = 10000;
const int MAX_INT = ~(1<<31);

int N, M; // N: num of app, M: mem of goal

vector<int> memVec(MAX_N);
vector<int> costVec(MAX_N);
// r: cost, c: app, val: max Mem
vector<vector<int>> table( MAX_COST+1, vector<int>(MAX_N, 0)); 

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for ( int i = 0; i < N; i++ )
        cin >> memVec[i];
    for ( int i = 0; i < N; i++ )
        cin >> costVec[i];

    for ( int costIdx = 0; costIdx <= MAX_COST; costIdx++ ){
        if ( costVec[0] <= costIdx ){
            table[costIdx][0] = memVec[0];
        }
    }
    for ( int appIdx = 1; appIdx < N; appIdx++ ){
        for ( int costIdx = 0; costIdx <= MAX_COST; costIdx++ ){
            int remainCost = costIdx - costVec[appIdx];
            int newMem;
            if ( remainCost < 0 )
                newMem = 0;
            else {
                newMem = table[remainCost][appIdx-1] + memVec[appIdx];
            }

            if ( table[costIdx][appIdx-1] < newMem )
                table[costIdx][appIdx] = newMem;
            else 
                table[costIdx][appIdx] = table[costIdx][appIdx-1];
        }
    }

    int lastAppIdx = N -1;
    for ( int costIdx = 0; costIdx <= MAX_COST; costIdx++ ){
        if( table[costIdx][lastAppIdx] >= M ){
            cout << costIdx;
            break;
        }
    }
}