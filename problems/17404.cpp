#include <iostream>
#include <vector>
using namespace std;

const int MAX_INT = ~(1<<31);
const int NUM_COLORS = 3;
const int MAX_HOUSES = 1000;

int N;

// [houseIdx][starting color][cur color]
vector<vector<vector<int>>> dpTable( 
    MAX_HOUSES+1, vector<vector<int>>(
        NUM_COLORS, vector<int>(
            NUM_COLORS, 0
        )
    )
);
// [hi][color]
vector<vector<int>> costs(
    MAX_HOUSES+1, vector<int>(
        NUM_COLORS, 0
    )
);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int n = 1; n <= N; n++ ){
        int cr, cg, cb;
        cin >> cr >> cg >> cb;
        costs[n][0] = cr;
        costs[n][1] = cg;
        costs[n][2] = cb;
    }

    for ( int r = 0; r < NUM_COLORS; r++ ){
        for ( int c = 0; c < NUM_COLORS; c++ ){
            dpTable[1][r][c] = r==c ? costs[1][r] : MAX_INT;
        }
    }        
    for ( int sc = 0; sc < NUM_COLORS; sc++ ){ 
        for ( int hi = 2; hi <= N; hi++ ){
            for ( int cc = 0; cc < NUM_COLORS; cc++ ){
                int prevC1 = (cc+1)%NUM_COLORS;
                int prevC2 = (cc+2)%NUM_COLORS;
                int new1, new2;
                if ( ((hi==N||hi==2)&&sc==cc) || dpTable[hi-1][sc][prevC1] == MAX_INT )
                    new1 = MAX_INT;
                else 
                    new1 = dpTable[hi-1][sc][prevC1] + costs[hi][cc];
                if ( ((hi==N||hi==2)&&sc==cc) || dpTable[hi-1][sc][prevC2] == MAX_INT )
                    new2 = MAX_INT;
                else 
                    new2 = dpTable[hi-1][sc][prevC2] + costs[hi][cc];
                //int new1 = ((hi==N||hi==2)&&sc==cc) ? MAX_INT : dpTable[hi-1][sc][prevC1] + costs[hi][cc];
                // int new2 = ((hi==N||hi==2)&&sc==cc) ? MAX_INT : dpTable[hi-1][sc][prevC2] + costs[hi][cc];
                printf( "hi[%d]sc[%d]cc[%d] >> new1:%d, new2: %d\n", hi, sc, cc, new1, new2 );//Debug
                dpTable[hi][sc][cc] = min( new1, new2);
            }
        }
    }

    int rst = MAX_INT;
    for ( int sc = 0; sc < NUM_COLORS; sc++ ){
        for ( int ec = 0; ec < NUM_COLORS; ec++ ){
            rst = rst > dpTable[N][sc][ec] ? dpTable[N][sc][ec] : rst;
        }
    }
    cout << rst;

    return 0;
}