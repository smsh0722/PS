#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;

vector<int> maleUp;
vector<int> maleDown;
vector<int> femUp;
vector<int> femDown;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int ni = 0; ni < N; ni++ ){
        int h;
        cin >> h;
        if ( h > 0 )
            maleUp.push_back(h);
        else 
            maleDown.push_back(-h);
    }
    for ( int ni = 0; ni < N; ni++ ){
        int h;
        cin >> h;
        if ( h > 0 )
            femUp.push_back(h);
        else 
            femDown.push_back(-h);
    }

    sort( maleUp.begin(), maleUp.end() );
    sort( maleDown.begin(), maleDown.end() );
    sort( femUp.begin(), femUp.end() );
    sort( femDown.begin(), femDown.end() );

    int ans = 0;

    {
        int fi = 0;
        for( auto m : maleUp ){
            while ( fi < int(femDown.size()) ){
                int f = femDown[fi];
                fi++;
                if ( m < f ){
                    ans++;
                    break;
                }
            }
        }
    }
    {
        int mi = 0;
        for ( auto f : femUp ){
            while ( mi < int(maleDown.size()) ){
                int m = maleDown[mi];
                mi++;
                if ( f < m ){
                    ans++;
                    break;
                }
            }
        }
    }

    cout << ans;
    return 0;
}