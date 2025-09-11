/* NOTE: DP + DFS
Naive로 푸는 과정을 관찰하면 수차례 공격 이후 동일한 체력 조합이 만들어질 수 있는 것을 확인할 수 있다.
따라서 DP 문제이다.

현재는 DFS로 모든 조합을 조사하고 있다.

그러나 DFS를 할 때 깊이가 최소인 것을 찾는 문제이므로, BFS를 쓰면 조금이라도 덜 조사할 수 있다.
*/
#include <iostream>
#include <vector>
using namespace std;

const int MAX_HP = 60;
const int MAX_ATTACK_COUNT = 60;
const vector<vector<int>> ATTACKS = {
    {9, 3, 1},
    {9, 1, 3},
    {3, 9, 1},
    {3, 1, 9},
    {1, 3, 9},
    {1, 9, 3}
};

// Num of SCV
int N;

vector<vector<vector<int>>> dpMemo(
    MAX_HP+1, vector<vector<int>>(
        MAX_HP+1, vector<int>(
            MAX_HP+1, -1
        )
    )
);

int DFS( int a, int b, int c )
{
    a = max(a, 0);
    b = max(b, 0);
    c = max(c, 0);
    // Fin Case
    if ( a == 0 && b == 0 && c == 0){
        return 0;
    }
    // Old Case
    if ( dpMemo[a][b][c] != -1 )
        return dpMemo[a][b][c];

    // New Case
    int minAttackCount = MAX_ATTACK_COUNT+1;
    for ( size_t ai = 0; ai < ATTACKS.size(); ai++ ){
        int attackCount = 1 + DFS( a - ATTACKS[ai][0], b - ATTACKS[ai][1], c - ATTACKS[ai][2] );
        minAttackCount = min( minAttackCount, attackCount );
    }

    return dpMemo[a][b][c] = minAttackCount;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    int HPs[3] = {0};
    for ( int i = 0; i < N; i++ )
        cin >> HPs[i];

    cout << DFS(HPs[0], HPs[1], HPs[2]);

    return 0;
}