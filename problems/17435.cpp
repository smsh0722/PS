/* NOTE:
Naive 하게 풀면 n번 들어가보면 된다.
그러나 시간복잡도 개선이 필요하다.

잘 생각해보면 이전에 조사했던 값을 재사용할 수 있을 것이다.
그러나, 이를 모두 저장하기엔 공간 복잡도에 문제가 있다.

어떻게 하면 좋을까?

2의 거듭제곱인 fn만 저장하면 된다.
이는 LCA에서 사용한 아이디어와 비슷하다.
이를 sparse table 이라고 부른다고한다.
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_M = 200000;
const int MAX_N = 500000;
const int logN = ceil(log2(MAX_N));

// Set range
int M;
// # of Queries
int Q;
// Query Fn(x)
int N, X;

// fTalbe[x][n] = Fn(x)
vector<vector<int>> fTable( MAX_M + 1, vector<int>(logN+1, 0) );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> M;
    for ( int mi = 1; mi <= M; mi++ ){
        cin >> fTable[mi][0];
    }

    for ( int n = 1; n <= logN; n++ ){
        for ( int x = 1; x <= M; x++ ){
            fTable[x][n] = fTable[fTable[x][n-1]][n-1];
        }
    }

    cin >> Q;
    for ( int qi = 0; qi < Q; qi++ ){
        int n, x;
        cin >> n >> x;
        
        int i = 0;
        while ( i <= logN ){
            if( (1<<i)&n ){
                x = fTable[x][i];
            }
            i++;
        }

        cout << x << "\n";
    }

    return 0;
}