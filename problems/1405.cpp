/* NOTE: 메모리 초과
첫 가능 4칸 * 다음칸 최대 3칸^13번 6,377,292 이다.
따라서, 그냥 backtracking으로도 풀린다. 
dp를 사용하면 조금 빠르긴 하지만, 메모리가 과하게 사용된다.

따라서, 문제를 풀 때는 항상 Naive 풀이의 시공간 복잡도 분석
해결 안 될 시에 차츰차츰 아이디어를 입히는 순서로 풀자.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+( const Vec2& other ) const {
        return {r+other.r, c+other.c};
    }
};

const int WORLD_ROW = 29;
const int WORLD_COL = 29;
const int WORLD_SIZE = WORLD_ROW*WORLD_COL;
const vector<Vec2> MOVES = { 
    {0,1},
    {0,-1},
    {1,0},
    {-1,0}
};

int N;

// e, w, s, n;
vector<double> moveProbs(4);

string world(WORLD_SIZE, '0');

unordered_map<string, double> memo;

inline int CalcualteVec2ToIdx( const Vec2& v )
{
    return v.r*WORLD_COL+v.c;
}

inline void SetWorldAt( const Vec2& pos, char c )
{
    world[CalcualteVec2ToIdx(pos)] = c;
}

inline void PrintWorld( )
{
    int i = 0;
    for ( int r = 0; r < WORLD_ROW; r++ ){
        for ( int c = 0; c < WORLD_COL; c++ ){
            cout << world[i++];
        }cout<<endl;
    }
}
double CalculateRecursive( const int count, const Vec2& pos )
{
    // cout << "Count: " << count << endl;
    // PrintWorld();
    
    if ( count == 0 )
        return 1.0;
    if ( memo.find(world) != memo.end() )
        return memo[world];

    double rst = 0;
    SetWorldAt( pos, '1'); // 현재(이전) 위치는 1로
    for ( int i = 0; i < 4; i++ ){
        double prob = moveProbs[i];
        if ( prob == 0 ) 
            continue;

        Vec2 move = MOVES[i];
        Vec2 nextPos = pos+move;
        if( nextPos.r < 0 || nextPos.r >= WORLD_ROW || nextPos.c < 0 || nextPos.c >= WORLD_COL )
            continue;
        if ( world[CalcualteVec2ToIdx(nextPos)] != '0' )
            continue;

        SetWorldAt( nextPos, '2' ); // 다음 위치는 2로
        rst += prob*CalculateRecursive( count-1, nextPos);
        SetWorldAt( nextPos, '0'); // 다음 위치 제거
    }

    SetWorldAt(pos,'2');
    return memo[world] = rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int i = 0; i < 4; i++ ){
        double p;
        cin >> p;
        moveProbs[i] = p/100.0;
    }

    Vec2 startPos = {14,14};
    SetWorldAt(startPos,'2');
    
    cout << fixed; cout.precision(10);
    cout << CalculateRecursive( N,  startPos);

    return 0;
}