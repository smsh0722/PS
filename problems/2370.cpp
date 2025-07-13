#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_PRESSED_RANGE = 20000;

int N;

struct Poster{
    int l;
    int r;
};

vector<Poster> posters;
vector<int> positinos;
vector<bool> bOccupied;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    for ( int i = 0; i < N; i++ ){
        int l, r;
        cin >> l >> r;
        posters.push_back(Poster{l,r});
        positinos.push_back(l);
        positinos.push_back(r);
    }

    sort( positinos.begin(), positinos.end());
    positinos.erase( unique( positinos.begin(), positinos.end() )
        , positinos.end() );

    int ans = 0;
    bOccupied.resize( MAX_PRESSED_RANGE, false );
    for ( int i = N-1; i >= 0; i-- ){
        Poster p = posters[i];
        int pressedL = lower_bound(positinos.begin(), positinos.end(), p.l ) - positinos.begin();
        int pressedR = lower_bound(positinos.begin(), positinos.end(), p.r ) - positinos.begin();
        // printf( "lr(%d, %d) to plr(%d,%d)\n", p.l, p.r, pressedL, pressedR);// DEbug
        bool bCanBeWatched = false;
        for ( int idx = pressedL; idx <= pressedR; idx++ ){
            if ( bOccupied[idx] == false )
                bCanBeWatched = true;
            bOccupied[idx] = true;
        }
        ans = bCanBeWatched ? ans + 1 : ans;
    }

    cout << ans;

    return 0;
}