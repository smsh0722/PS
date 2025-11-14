/* NOTE:
어처피 매번 합을 구한다면, 미리 합을 구해놓으면 중복되는 계산을 줄일 수 있지 않을까?
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Snowman{
    int h;
    int i, j;
};

int N;

vector<int> snowballs;
vector<Snowman> snowmans;

bool CompareSnowmanAscByHeight( const Snowman& a, const Snowman& b )
{
    return a.h < b.h;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    snowballs.resize(N);
    for ( int ni = 0; ni < N; ni++ ){
        cin >> snowballs[ni];
    }

    snowmans.reserve(N*N);
    for ( int i = 0; i < N; i++ ){
        for ( int j = i+1; j < N; j++ )
            snowmans.push_back({snowballs[i]+snowballs[j], i, j} );
    }

    sort( snowmans.begin(), snowmans.end(), CompareSnowmanAscByHeight );

    int ans = INT32_MAX;
    for ( size_t i = 0; i < snowmans.size(); i++ ){
        for ( size_t j = i+1; j < snowmans.size(); j++ ){
            const Snowman& a = snowmans[i];
            const Snowman& b = snowmans[j];

            if ( a.i != b.i && a.i != b.j && a.j != b.i && a.j != b.j ){
                ans =  min( ans, b.h - a.h );
                break;
            }
        }
    }
    cout << ans;
    return 0;
}