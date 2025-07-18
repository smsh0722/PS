#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int M; // num of shooting point
int N; // num of animals
int L; // num of rifle range

vector<int> shootingPoints;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> M >> N >> L;
    shootingPoints.resize(M, 0);
    for ( int i = 0; i < M; i++ ){
        cin >> shootingPoints[i];
    }
    sort( shootingPoints.begin(), shootingPoints.end() );

    int count = 0;
    for ( int i = 0; i < N; i++ ){
        int x,y;
        cin >> x >> y;
        
        if ( y > L )
            continue;
        int yDiff = L - y;
        int lx = x - yDiff;
        int rx = x + yDiff;

        int lIdx = lower_bound(shootingPoints.begin(), shootingPoints.end(), lx ) 
                    - shootingPoints.begin();
        int rIdx = upper_bound(shootingPoints.begin(), shootingPoints.end(), rx )
                    - shootingPoints.begin();
        if ( lIdx < rIdx )
            count++;
    }

    cout << count;

    return 0;
}