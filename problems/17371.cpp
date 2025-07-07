#include <iostream>
#include <vector>

using namespace std;

struct Vec2{
    int x, y;
};

const int MAX_INT = ~(1<<31);
const int MAX_N = 1000;
int N;

vector<Vec2> buildings(MAX_N);

inline int GetDistance( const Vec2& a, const Vec2& b )
{
    int xDiff = a.x - b.x;
    int yDiff = a.y - b.y;

    int rst = (xDiff * xDiff) + (yDiff * yDiff);
    return rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    {
        int x, y;
        for( int i = 0; i < N; i++ ){
            cin >> x >> y;
            buildings[i] = Vec2{x,y};
        }
    }   

    Vec2 hPos = buildings[0];
    int minDist = MAX_INT;
    for ( int i = 0; i < N; i++ ){
        Vec2 srcPos = buildings[i];
        int localMaxDist = -1;
        for ( int j = 0; j < N; j++ ){ // NOTE: 시작점이 달라지면 이전에 계산한 쌍도 다시 조사할 필요 있음.
            if ( j == i )  continue;

            Vec2 dstPos = buildings[j];
            int newDist = GetDistance( srcPos, dstPos );
            if ( localMaxDist < newDist ){
                localMaxDist = newDist;
            }
        }

        if ( localMaxDist == -1 )
            continue;

        if ( minDist > localMaxDist ){
            hPos = srcPos;
            minDist = localMaxDist;
        }
    }

    printf( "%.12f %.12f", double(hPos.x), double(hPos.y) );
}