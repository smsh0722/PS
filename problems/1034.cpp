#include <iostream>
#include <vector>
#include <string>
using namespace std;

// size of row
int R;
// size of column
int C;
// num of operationss
int K;
// Answer
int ans = 0;

vector<string> ramps;

inline void ClickSwitch( vector<string>& trg, int c )
{
    for ( int r = 0; r < R; r++ ){
        trg[r][c] = trg[r][c] == '0' ? '1' : '0';
    }
}
inline int CheckRow( const vector<string>& trg )
{
    int rst = 0;
    for ( int r = 0; r < R; r++ ){
        bool bFlag = true;
        for ( int c = 0; c < C; c++ ){
            if ( trg[r][c] == '0' ){
                bFlag = false;
                break;
            }
        }
        rst += bFlag == true ? 1 : 0;
    }
    return rst;
}
int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> R >> C;
    ramps.resize(R);
    for ( int r = 0; r < R; r++ ){
        cin >> ramps[r];
    }
    cin >> K;

    for ( int r = 0; r < R; r++ ){
        vector<string> tmp = ramps;
        int switchCount = 0;
        int localAns = 0;
        for ( int c = 0; c < C; c++ ){
            if ( tmp[r][c] == '0'){
                switchCount++;
                ClickSwitch(tmp, c);
            }
        }
        
        if ( switchCount > K )
            continue;
        if ( (switchCount&1) != (K&1) )
            continue;
        
        localAns = CheckRow(tmp);
        ans = ans < localAns ? localAns : ans;
    }

    cout << ans;

    return 0;
}