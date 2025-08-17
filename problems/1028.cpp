/* NOTE:
모든 사이즈 조사하는 것보다 빠르게 하기 위하여, binary search로 사이즈 찾음.
그러나, 이는 틀림. 모든 걸 다 조사해야함.
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct Vec2{
    int r, c;
};

struct DiagonalSum{
    int lu, ld, ru, rd;
};

const int MAX_DIAMOND_SIZE = 375;

vector<vector<DiagonalSum>> diagonalSums;
vector<vector<bool>> world;

int R, C;

bool IsExistDiamond( const int diaSize, const Vec2 pos, int depth )
{
    if ( pos.r < 0 || pos.r >= R || pos.c < 0 || pos.c >= C )
        return false;

    int posDiff = diaSize - 1;
    switch (depth)
    {
        case 0:
        {   
            if ( diagonalSums[pos.r][pos.c].lu < diaSize )
                return false;
            return IsExistDiamond(diaSize, {pos.r-posDiff, pos.c-posDiff}, 1 );
        }
        case 1:
        {
            if ( diagonalSums[pos.r][pos.c].ld < diaSize )
                return false;
            return IsExistDiamond(diaSize, {pos.r+posDiff, pos.c-posDiff}, 2);
        }
        case 2: 
        {
            if ( diagonalSums[pos.r][pos.c].rd < diaSize )
                return false;
            return IsExistDiamond(diaSize, {pos.r+posDiff, pos.c+posDiff}, 3 );
        }
        case 3:
        {
            if ( diagonalSums[pos.r][pos.c].ru < diaSize )
                return false;
            return true;
        }
        default:
            break;
    }
    
    return false;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> R >> C;

    diagonalSums.resize(R, vector<DiagonalSum>(C,{0,0,0,0}) );
    world.resize(R, vector<bool>(C));

    for ( int r = 0; r < R; r++ ){
        string s;
        cin >> s;
        for ( int c = 0; c < C; c++ ){
            world[r][c] = (s[c] == '1');
        }
    }

    // Preproc 1 
    for ( int r = R-1; r >=0; r-- ){
        for ( int c = C-1; c >=0; c-- ){
            if (world[r][c] == false )
                continue;

            diagonalSums[r][c].ld = 1;
            diagonalSums[r][c].rd = 1;
            if ( r + 1 >= R )
                continue;
            if ( c - 1 >= 0 ){
                diagonalSums[r][c].ld += diagonalSums[r+1][c-1].ld;
            }
            if ( c + 1 < C ){
                diagonalSums[r][c].rd += diagonalSums[r+1][c+1].rd;
            }
        }
    }
    // Preproc 2
    for ( int r = 0; r < R; r++ ){
        for ( int c = 0; c < C; c++ ){
            if ( world[r][c] == false )
                continue;
            
            diagonalSums[r][c].lu = 1;
            diagonalSums[r][c].ru = 1;
            if ( r-1 < 0 )
                continue;
            if ( c-1 >= 0 ){
                diagonalSums[r][c].lu += diagonalSums[r-1][c-1].lu;
            }
            if ( c+1 < C ){
                diagonalSums[r][c].ru += diagonalSums[r-1][c+1].ru;
            }
        }
    }

    // Solve
    int ans = 0;
    for ( int trgSize = MAX_DIAMOND_SIZE; trgSize >= 1; trgSize-- ){
        bool bExist = false;
        for ( int r = 0; r < R; r++ ){
            for ( int c = 0; c < C; c++ ){
                if ( IsExistDiamond(trgSize, {r,c}, 0) ){
                    bExist = true;
                    break;
                }
            }
            if ( bExist == true ){
                break;
            }
        }

        if ( bExist == true ){
            ans = ans < trgSize ? trgSize: ans;
            break;
        }
    }

    cout << ans;

    return 0;
}