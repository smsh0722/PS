/* NOTE:
backtracking 문제이다.
dp를 쓰기도 애매하고, greedy한 방법은 너무 복잡하다.

또한, 같은 backtracking 이더라도, 흑과 백자리는 서로 영향을 안주므로 따로 계산해야 time complexity 줄어든다.
2^100 -> 2^50
*/
#include <iostream>
#include <vector>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+(const Vec2& other ) const {
        return {r+other.r, c+other.c};
    }
    Vec2 operator*(const int v ) const {
        return {r*v, c*v};
    }
};

const int MAX_N = 10;

int n;
int diagN;
vector<vector<int>> world(MAX_N, vector<int>(MAX_N, 0 ) );
vector<bool> sumDiag(MAX_N*2-1, false);
vector<bool> diffDiag(MAX_N*2-1, false);

inline int GetSumDiagIdx( const Vec2& pos ){
    return pos.r + pos.c;

}
inline int GetDiffDiagIdx(const Vec2& pos ){
    return pos.r - pos.c + n - 1;
}
inline int IsPossible( const Vec2& pos )
{
    if ( world[pos.r][pos.c] == 0 )
        return false;

    int sumIdx = GetSumDiagIdx(pos);
    int diffIdx = GetDiffDiagIdx(pos);
    if ( sumDiag[sumIdx] == true )
        return false;
    if ( diffDiag[diffIdx] == true )
        return false;
    return true;
}
int SolveRecursive( const size_t ci, const vector<Vec2>& candidate )
{  
    if ( ci >= candidate.size() )
        return 0;

    Vec2 pos = candidate[ci];
    bool bPossible = IsPossible(pos);
    int rst1 = 0;
    int rst2 = 0;

    // 현재에 둔다.
    if ( bPossible == true ){
        int sumIdx = GetSumDiagIdx(pos);
        int diffIdx = GetDiffDiagIdx(pos);

        sumDiag[sumIdx] = true;
        diffDiag[diffIdx] = true;
        rst1 = SolveRecursive(ci+1, candidate) + 1;
        sumDiag[sumIdx] = false;
        diffDiag[diffIdx] = false;
    }
    // 현재에 안 둔다.
    rst2 = SolveRecursive(ci+1, candidate);

    return max(rst1, rst2);
}

int main( void )
{
    ios_base::sync_with_stdio(false);

    cin >> n;
    for ( int r = 0; r < n; r++ ){
        for ( int c = 0; c < n; c++ ){
            int v;
            cin >> v;
            if ( v == 1 ){
                world[r][c] = 1;
            }
        }
    }

    vector<Vec2> black;
    vector<Vec2> white;
    for ( int r = 0; r < n; r++ ){
        for ( int c = 0; c < n; c++ ){
            if ( (r+c)%2==0 )
                black.push_back({r,c});
            else 
                white.push_back({r,c});
        }
    }
    cout << SolveRecursive( 0, black) + SolveRecursive(0, white);
    return 0;
}