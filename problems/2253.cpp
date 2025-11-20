#include <iostream>
#include <vector>
using namespace std;

const int INF = INT32_MAX;
const int MAX_SPEED = 150;

// # of steps
int N;
// # of invalid steps
int M;

vector<bool> bSteps;

// table[speed][step idx] = min step+1
vector<vector<int>> table;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    bSteps.resize(N+1, true);
    for ( int mi = 0; mi < M; mi++ ){
        int step;
        cin >> step;
        bSteps[step] = false;
    }

    table.resize(MAX_SPEED+1, vector<int>(N+1, INF ));
    table[0][1] = 1;

    for ( int step = 2; step <= N; step++ ){
        if ( bSteps[step] == false )
            continue;
        for ( int speed = 1; speed < MAX_SPEED; speed++ ){
            int prevStep = step - speed;
            if ( prevStep < 1 )
                continue;

            table[speed][step] = min( table[speed][step], table[speed-1][prevStep]);
            table[speed][step] = min( table[speed][step], table[speed][prevStep]);
            table[speed][step] = min( table[speed][step], table[speed+1][prevStep]);
            if ( table[speed][step] < INF )
                table[speed][step]++;
        }
    }

    int ans = INF;
    for ( int speed = 1; speed < MAX_SPEED; speed++ ){
        if ( table[speed][N] == 0 )
            continue;
        ans = min( ans, table[speed][N] );
    }

    if ( ans == INF)
        cout << -1;
    else 
        cout << ans-1;

    return 0;
}