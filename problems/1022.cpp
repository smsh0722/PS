/* NOTE:
아이디어 떠올리는 데 당황!

그러나 역시 가장 기본은 Naive 관찰!

Naive로 소용돌이 순서대로 번호 채우면 매우 쉬움. 시간도 가능할 것 같은데 공간이 안 됨.
어떻게 하지?
규칙을 찾을까? 공간 단축할 아이디어 있을까?

규칙. 열심히 노력해 봤지만 껍질의 꼭짓점 밖에 없음.

Naive에서 변형하여 필요한 껍질만 전수 조사? 공간도 될 것임.

껍질 번호 찾는 법만 발견하면 끝. => max( r, c)
*/
#include <iostream>
#include <vector>
#include <cmath>
#include <string>
#include <iomanip>
using namespace std;

int r1, r2, c1, c2;

vector<vector<int>> grid;
vector<bool> bOnions(5001, false);
int maxNum = 0;

inline bool IsInbound( int r, int c)
{
    if ( r < r1 || r2 < r || c < c1 || c2 < c )
        return false;
    return true;
}
inline void SetGrid( int r, int c, int val )
{
    grid[r-r1][c-c1] = val;
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> r1 >> c1 >> r2 >> c2;
    grid.resize( r2-r1+1, vector<int>(c2-c1+1) );
    
    // 필요한 껍질 찾기
    for ( int r = r1; r <= r2; r++ ){
        for ( int c = c1; c <= c2; c++ ){
            int onion = max( abs(r), abs(c) );
            bOnions[onion] = true;
        }
    }

    // Loop: 껍질s
        // 필요한 껍질 하나 완성->집어 넣기
    for ( int oi = 0; oi <= 5000; oi++ ){
        if ( bOnions[oi] == false )
            continue;
        if ( oi == 0 ){
            IsInbound(0, 0);
            SetGrid(0,0, 1);
            continue;
        }

        int r = oi-1;
        int c = oi;
        
        int x = (oi-1)*2+1;
        int num = x*x;
        // 우면
        for ( ; r >= -oi; r-- ){
            num++;
            if ( IsInbound(r, c) ){
                SetGrid(r, c, num);
                maxNum = max(maxNum, num);
            }
        } r++; c--;
        // 상면
        for ( ; c >= -oi; c-- ){
            num++;
            if ( IsInbound(r, c) ){
                SetGrid(r, c, num);
                maxNum = max(maxNum, num);
            }
        } c++; r++;
        // 좌면
        for ( ; r <= oi; r++ ){
            num++;
            if ( IsInbound(r, c) ){
                SetGrid(r, c, num);
                maxNum = max(maxNum, num);
            }
        } r--; c++;
        // 하면
        for ( ; c <= oi; c++ ){
            num++;
            if ( IsInbound(r, c) ){
                SetGrid(r, c, num);
                maxNum = max(maxNum, num);
            }
        }
        // NOTE: loop가 끝난 뒤 loop var이 어느 값에 있을지 생각하자!
        // r++, r--, c++, c-- 안해서 헤맸다.
    }

    // Answer
    int maxLength = to_string(maxNum).length();
    cout.setf(ios::right); // NOTE: setf()
    for ( int r = r1; r <= r2; r++ ){
        for ( int c = c1; c <= c2; c++ ){
            cout << setw(maxLength) << grid[r-r1][c-c1] << " "; // NOTE: setw()
        }
        cout << "\n";
    }

    return 0;
}