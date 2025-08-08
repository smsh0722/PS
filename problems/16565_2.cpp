/* NOTE:
combinations 을 구하기 위해
파스칼 + dp를 사용 O(N^2)
*/
#include <iostream>
#include <vector>
using namespace std;

const int MAX_LEFT = 52;
const int NUM_OF_FACE = 13;
const int64_t DIVISOR = 10007;

int N; // num of picks

// [left][card face]
vector<vector<int64_t>> dpTable(MAX_LEFT+1, vector<int64_t>(NUM_OF_FACE+1, 0));
vector<vector<int64_t>> combinations(MAX_LEFT+1, vector<int64_t>(MAX_LEFT+1,1));

inline void BuildCombinations( )
{
    /* pascal
      2C0 2C1 2C2
    3C0 3C1 3C2 3C3
    */
    for ( int n = 2; n <= MAX_LEFT; n++ ){
        for ( int r = 1; r < n; r++ ){
            combinations[n][r] = combinations[n-1][r-1] + combinations[n-1][r];
        }
    }

}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    BuildCombinations();

    cin >> N;

    dpTable[0][1] = 1;
    dpTable[1][1] = 4;
    dpTable[2][1] = 6;
    dpTable[3][1] = 4;
    for ( int card = 2; card <= NUM_OF_FACE; card++ ){
        for ( int left = 0; left <= MAX_LEFT; left++ ){
            for ( int pick = 0; (pick < 4)&&(left - pick >= 0); pick++ ){
                dpTable[left][card] += combinations[4][pick]*dpTable[left-pick][card-1];
                dpTable[left][card] %= DIVISOR;
            }
        }
    }

    cout << (combinations[52][N] - dpTable[N][13])%DIVISOR << endl;

    return 0;
}