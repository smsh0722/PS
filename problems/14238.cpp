/* NOTE:
&(참조) 는 대상 처음 정의 때 고정, 도중에 바꿀 수 없음

축에 대해 잘 고민하자. 처음엔 b를 둘수 있냐, c를 둘수 있냐를 기준으로 4가지로 나누었지만.
잘 생각해보면 9가지로 나누어야 한다.

struct 생성자와 vector 개념
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

enum Status{
    UNKNOWN, FAILED, SUCCESS
};

struct Cases{
    Status ab[3][3];
    Cases(){ for ( int r = 0; r < 3; r++){for(int c= 0; c < 3; c++ ){ab[r][c] = UNKNOWN;}}};
};

const int MAX_NUM = 50;

string s="";
string ans="";
int countABC[3] = {0};
vector<vector<vector<Cases>>> dpMemo( MAX_NUM+1, vector<vector<Cases>>(MAX_NUM+1, vector<Cases>(MAX_NUM+1)));

Status SolveRecursive( int bDist, int cDist )
{
    if ( countABC[0] == 0 && countABC[1] == 0 && countABC[2] == 0){
        cout << ans << endl;
        return SUCCESS;
    }
    
    Status* s = &dpMemo[countABC[0]][countABC[1]][countABC[2]].ab[bDist][cDist];
    if ( *s != UNKNOWN )
        return *s;

    if( countABC[0] > 0 ){
        ans += "A";
        countABC[0]--;
        if ( SolveRecursive(max(0, bDist-1), max(0,cDist-1) ) == SUCCESS )
            return SUCCESS;
        ans.pop_back();
        countABC[0]++;
    }
    if ( countABC[1] > 0 && bDist <= 0 ){
        ans += "B";
        countABC[1]--;
        if ( SolveRecursive(1, max(0, cDist-1 ) ) == SUCCESS )
            return SUCCESS;
        ans.pop_back();
        countABC[1]++;
    }
    if ( countABC[2] > 0 && cDist <= 0){
        ans += "C";
        countABC[2]--;
        if ( SolveRecursive(max(0, bDist-1), 2) == SUCCESS )
            return SUCCESS;
        ans.pop_back();
        countABC[2]++;
    }

    return (*s = FAILED);
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> s;
    for ( auto c: s ){
        countABC[c-'A']++;
    }

    if ( SolveRecursive(0,0) != SUCCESS )
        cout << -1 << endl;

    return 0;
}