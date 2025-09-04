#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Dist from src to dst
int D;
// Num of Stepping stones
int N;
// Num of elimination
int M;

vector<int> steppingStones;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> D >> N >> M;
    steppingStones.resize(N+2);
    steppingStones[0] = 0;
    steppingStones[N+1] = D;
    for ( int i = 1; i <= N; i++ ){
        cin >> steppingStones[i];
    }
    sort( steppingStones.begin(), steppingStones.end() );

    int rst = -1;
    int l = 0; 
    int r = D;
    while ( l <= r ){
        int mid = (r-l)/2+l;

        int stoneIdx = 0;
        int skipCount = 0;
        while ( stoneIdx < N+1 ){
            int nextIdx = stoneIdx + 1;
            int dist = steppingStones[nextIdx] - steppingStones[stoneIdx];

            if ( dist >= mid ){
                stoneIdx = nextIdx;
                continue;
            }

            for (; nextIdx <= N+1; nextIdx++ ){
                if ( steppingStones[nextIdx] - steppingStones[stoneIdx] >= mid ){
                    // printf("[%d]: skip from %d to %d\n", mid, stoneIdx, nextIdx);
                    skipCount += (nextIdx-stoneIdx-1);
                    stoneIdx = nextIdx;
                    break;
                }
            }
            if ( nextIdx == N+2 ){
                skipCount += (nextIdx-stoneIdx-1);
                break;
            }
        }

        if ( skipCount <= M ){
            rst = mid;
            l = mid+1;
        }
        else { // skipCount > M
            r = mid-1;
        }
    }

    cout << rst;

    return 0;
}