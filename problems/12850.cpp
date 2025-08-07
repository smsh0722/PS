/* NOTE:
DP가 떠오르는 문제이다. 다만, space는 축{시간:{prev, cur}, 빌딩} 으로 유지해서 관리하더라도,
Time은 아무리 해도 해결할 수 가 없다.

시간을 단축시키기 위한 방법으로 다른 아이디어를 떠올려야 한다.

행렬 관점 + exponentiation_by_squaring 방법을 써야한다. 
*/

#include <iostream>
#include <vector>
using namespace std;

const int BUILDING_NUM = 8;
const int MODULO = 1000000007;

vector<vector<int64_t>> matrix = {
    {0,1,0,0,0,1,0,0}, 
    {1,0,1,0,0,1,0,0},
    {0,1,0,1,0,1,1,0},
    {0,0,1,0,1,0,1,0},
    {0,0,0,1,0,0,0,1},
    {1,1,1,0,0,0,1,0},
    {0,0,1,1,0,1,0,1},
    {0,0,0,0,1,0,1,0},
};
vector<vector<int64_t>> ans = {
    {1,0,0,0,0,0,0,0},
    {0,1,0,0,0,0,0,0},
    {0,0,1,0,0,0,0,0},
    {0,0,0,1,0,0,0,0},
    {0,0,0,0,1,0,0,0},
    {0,0,0,0,0,1,0,0},
    {0,0,0,0,0,0,1,0},
    {0,0,0,0,0,0,0,1},
};

int D;

void Debug( const vector<vector<int64_t>>& mat )
{
    for ( int r = 0; r < BUILDING_NUM; r++ ){
        for ( int c = 0; c < BUILDING_NUM; c++ ){
            cout << mat[r][c] << " ";
        } cout << "\n";
    }
}

vector<vector<int64_t>> MulMat( const vector<vector<int64_t>>& a, const vector<vector<int64_t>>& b ){
    vector<vector<int64_t>> rst = vector<vector<int64_t>>(BUILDING_NUM, vector<int64_t>(BUILDING_NUM,0));

    for ( int r = 0; r < BUILDING_NUM; r++ ){
        for ( int c = 0; c < BUILDING_NUM; c++ ){
            for ( int c2 = 0; c2 < BUILDING_NUM; c2++ ){
                rst[r][c2] += a[r][c]*b[c][c2];
            }
        }
    }

    for ( int r = 0; r < BUILDING_NUM; r++ ){
        for ( int c = 0; c < BUILDING_NUM; c++ ){
            rst[r][c] %= MODULO;
        }
    }
    return rst;
};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> D;

    int mask= 1;
    while ( D > 0 ){
        { // Debug
            cout << "D: " << D << endl;
            cout << "----------Matrix----------\n";
            Debug(matrix);
            cout << "----------Ans----------\n";
            Debug(ans);
        }

        if ( (D&mask) == 1){
            ans = MulMat(ans, matrix);
        }

        matrix = MulMat(matrix, matrix);

        D = D>>1;
    }

    cout << ans[0][0];

    return 0;
}

