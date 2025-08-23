/* NOTE:
bruteforce 시간복잡도 가능. 구현 간단.

But, 수열의 길이도 자유이므로 매 길이마다 체크해야한다. 공차가 정해졌을 때 최대 길이만 탐색하여 틀렸다.

검토 순서)
1. 아이디어 이상 없는 지
2. 코드에 이상 없는 지
3. 테스트케이스 변형
순서대로 검토하는 습관 가지자
*/
#include <iostream>
#include <vector>
#include <string>
#include <cmath>
using namespace std;

const int MAX_DIFF = 8;

// Size of NxM matrix
int N, M;

// Talbe
vector<vector<int>> table;

inline bool IsSquareNum( const int num )
{
    int rootedNum = sqrt(num);
    return num == (rootedNum*rootedNum);
}

inline int FindMaxSquareNum( int r, int c )
{
    int rst = -1;
    const int originR = r;
    const int originC = c; 
    for ( int rd = -MAX_DIFF; rd <= MAX_DIFF; rd++ ){
        for ( int cd = -MAX_DIFF; cd <= MAX_DIFF; cd++ ){
            r = originR;
            c = originC;

            int num = 0;
            if ( rd == 0 && cd == 0 ){
                num = table[r][c];
                if ( IsSquareNum(num) == true ){
                    rst = rst < num ? num : rst ;
                }
            }
            else {
                while ( (0 <= r && r < N) && (0 <= c && c < M) ){
                    num = num*10 + table[r][c];
                    r += rd;
                    c += cd;
                    if ( IsSquareNum(num) == true ){
                        rst = rst < num ? num : rst ;
                    }
                }
            }
        }
    }
    return rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;
    table.resize( N, vector<int>(M, 0) );
    for ( int n = 0; n < N; n++ ){
        string s;
        cin >> s;

        for ( int m = 0; m < M; m++ ){
            table[n][m] = s[m] - '0';
        }
    }

    int ans = -1;
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            // Find Max SquareNum which starts current (r, c)
            int tmpNum = FindMaxSquareNum(r, c);
            ans = ans < tmpNum ? tmpNum : ans ;
        }
    }

    cout << ans;

    return 0;
}