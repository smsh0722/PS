/* NOTE:  DP + BFS
*/
#include <iostream>
#include <vector>
#include <queue>
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

struct Node {
    int a, b, c;
    int attackCount;
};

// Num of SCV
int N;

vector<vector<vector<bool>>> visited(
    MAX_HP+1, vector<vector<bool>>(
        MAX_HP+1, vector<bool>(
            MAX_HP+1, false
        )
    )
);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    int HPs[3] = {0};
    for ( int i = 0; i < N; i++ )
        cin >> HPs[i];

    // BFS
    queue<Node> q;
    q.push( {HPs[0], HPs[1], HPs[2], 0} );
    visited[HPs[0]][HPs[1]][HPs[2]] = true;
    while ( q.empty() == false )
    {
        Node cur = q.front();
        q.pop();

        int na, nb, nc;
        int nAttackCount = cur.attackCount + 1;
        for ( size_t ai = 0; ai < ATTACKS.size(); ai++ ){
            na = max( cur.a - ATTACKS[ai][0], 0 );
            nb = max( cur.b - ATTACKS[ai][1], 0 );
            nc = max( cur.c - ATTACKS[ai][2], 0 );
            
            if ( na == 0 && nb == 0 && nc == 0 ){
                cout << nAttackCount;
                return 0;
            }
            else if ( visited[na][nb][nc] == true ) 
                continue;
            else { // NOTE: QUEUE 터지는 것을 방지하기 위해선, 검증 후 필수적인 경우에만 넣는다.
                q.push( {na, nb, nc, nAttackCount});
                visited[na][nb][nc] = true;
            }
        }
    }

    return 0;
}