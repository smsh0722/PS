/* NOTE:
지문 대충 읽어 문제 생겼다.
도형 하나만 놓는다는 것을 여러개 놓는 방법으로 풀어버렸다.
지문은 항상 꼼꼼히 읽자
*/
#include <iostream>
#include <vector>
using namespace std;

struct Vec2{
    union {
        struct { int r, c; };
        struct { int x, y; };
    };
    Vec2 operator+( const Vec2& other ) const 
    {
        return {r+other.r, c+ other.c};
    }
};

const int NUM_OF_TERTOMINOS = 7;

int N, M;

int ans = 0;

vector<vector<int>> nums;
vector<vector<Vec2>> tertominos(NUM_OF_TERTOMINOS);

inline void CalSum( const int r, const int c, const vector<Vec2>& tertomino )
{
    int localSum = 0;
    for ( size_t i = 0; i < tertomino.size(); i++ ){
        const Vec2& pos = tertomino[i];
        const Vec2 worldPos = {pos.r + r, pos.c + c };
        localSum += nums[worldPos.r][worldPos.c];
    }
    ans = max( localSum, ans );
}   

inline void PlaceTertominos( const int r, const int c )
{
    // 놓아보기
    for ( size_t ti = 0; ti < tertominos.size(); ti++ ){
        const vector<Vec2>& tertomino = tertominos[ti]; // NOTE: reference 사용 유무가 속도 차이 크다.
        // Check Can be placed
        bool bCanPlace = true;
        for ( size_t i = 0; i < tertomino.size(); i++ ){
            const Vec2& pos = tertomino[i];
            const Vec2 worldPos = {pos.r + r, pos.c + c };
            if ( worldPos.r < 0 || worldPos.r >= N || 
                worldPos.c < 0 || worldPos.c >= M  ){

                bCanPlace = false;
                break;
            }
        }

        if ( bCanPlace == false )
            continue;

        CalSum(r, c, tertomino);
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    tertominos[0] = vector<Vec2>{ {0,0}, {0,1}, {0,2}, {0,3} };
    tertominos[1] = vector<Vec2>{ {0,0}, {0,1}, {1,0}, {1,1} };
    tertominos[2] = vector<Vec2>{ {0,0}, {0,1}, {1,1}, {2,1} };
    tertominos[3] = vector<Vec2>{ {0,0}, {1,0}, {1,1}, {2,1} };
    tertominos[4] = vector<Vec2>{ {0,0}, {0,1}, {0,2}, {1,1} };
    tertominos[5] = vector<Vec2>{ {0,0}, {0,-1}, {1,-1}, {2,-1} };
    tertominos[6] = vector<Vec2>{ {0,0}, {1,0}, {1,-1}, {2,-1} };
    for ( int ti = 0; ti < NUM_OF_TERTOMINOS; ti++ ){
        vector<Vec2> tertomino = tertominos[ti];

        for ( int rotate = 0; rotate < 3; rotate++ ){
            for ( size_t i = 0; i < tertomino.size(); i++ ){
                Vec2 pos = tertomino[i];
                tertomino[i] = {pos.c, -pos.r};
            }

            tertominos.push_back(tertomino);
        }
    }

    cin >> N >> M;

    nums.resize(N, vector<int>(M, 0));
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            cin >> nums[r][c];
        }
    }

    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < M; c++ ){
            PlaceTertominos(r, c);
        }
    }

    cout << ans;

    return 0;
}