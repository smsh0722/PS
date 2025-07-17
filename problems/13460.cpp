#include <iostream>
#include <vector>
#include <string>

using namespace std;

enum eStatus
{
    Success, Failed, NeedSearch    
};

struct Vec2{
    union {
        struct {int x, y; };
        struct {int r, c; };
    };
    Vec2 operator+(const Vec2& other ) const {
        return {(x+other.x), (y+other.y)};
    }
    bool operator==( const Vec2& other ) const {
        return (x == other.x && y==other.y);
    }
};

const int MAX_NM = 10;
const int MAX_INT = ~(1<<31);

const vector<Vec2> moveArr = { {-1, 0}, // u
                            {1,0}, // d
                            {0,-1}, // l
                            {0,1} // r
                        };
int N;
int M;

vector<vector<bool>> visited(MAX_NM*MAX_NM, vector<bool>(MAX_NM*MAX_NM, false )); // [rIdx][bIdx]
vector<vector<char>> world( MAX_NM, vector<char>(MAX_NM, '#'));

int FindMinSolRecursive( const Vec2& B, const Vec2& R, int count = 0 )
{
    // printf( "Count: %d\n", count); // Debug
    if ( count >= 10 )
        return MAX_INT;

    int rst = MAX_INT;
    for ( int m = 0; m < 4; m++ ){
        eStatus status = NeedSearch; // 1: success, 0: need to recursive, -1: failed
        Vec2 prevB = B;
        Vec2 prevR = R;
        while ( status != Failed ){
            Vec2 newB = prevB + moveArr[m];
            if ( newB.r < 0 || newB.r >= N || newB.c < 0 || newB.c >= M )
                newB = prevB;
            else if ( world[newB.r][newB.c] == 'O' ){
                status = Failed;
                world[prevB.r][prevB.c] = '.';
                break;
            }
            else if( world[newB.r][newB.c] != '.' )
                newB = prevB;
            else { //'.'
                world[prevB.r][prevB.c] = '.';
                world[newB.r][newB.c] = 'B';
            }

            Vec2 newR = prevR + moveArr[m];
            if ( status == Success )
                newR = prevR;
            else if ( newB.r < 0 || newB.r >= N || newB.c < 0 || newB.c >= M )
                newR = prevR;
            else if ( world[newR.r][newR.c] == 'O'){
                status = Success;
                world[prevR.r][prevR.c] = '.';
            }
            else if( world[newR.r][newR.c] != '.' )
                newR = prevR;
            else { // '.'
                world[prevR.r][prevR.c] = '.';
                world[newR.r][newR.c] = 'R';
            }

            if ( (newB == prevB) && (newR == prevR) ){ // nothing changed
                break;
            }

            prevB = newB;
            prevR = newR;
        }
        // printf("Done while: statue[%d]\n", status); // DEbug

        if ( status == NeedSearch ){
            int r = prevR.r * M + prevR.c;
            int c = prevB.r * M + prevB.c;
            if ( visited[r][c] == false ){
                visited[r][c] = true;
                int tmpCount = FindMinSolRecursive( prevB, prevR, count+1 );
                visited[r][c] = false;
                if ( tmpCount < MAX_INT )
                    rst = rst > tmpCount + 1 ? tmpCount + 1: rst;
            }
        }
        
        if ( world[prevB.r][prevB.c] == 'B' )
            world[prevB.r][prevB.c] = '.'; 
        world[B.r][B.c] = 'B'; 
        if ( world[prevR.r][prevR.c] == 'R' )
            world[prevR.r][prevR.c] = '.';
        world[R.r][R.c] = 'R'; 

        if ( status == Success ){
            rst = 1;
            break;
        }
    }

    return rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    Vec2 posB, posR;
    for ( int r = 0; r < N; r++ ){
        string s;
        cin >> s;
        for ( int c = 0; c < M; c++ ){
            world[r][c] = s.at(c);
            if ( s.at(c) == 'B' )
                posB = {r,c};
            else if (s.at(c) == 'R')
                posR = {r,c};
        }
    }

    int rst = FindMinSolRecursive( posB, posR );
    if ( rst == MAX_INT )
        cout << -1;
    else 
        cout << rst;

    return 0;
}