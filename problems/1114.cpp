/* NOTE: parametric_search
매개변수 탐색인 것은 금방 떠올릴 수 있다.
그러나 맨 왼쪽 커팅을 구하는 과정이 실수하기 좋다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// L of log
int L;
// # of cut pos
int K;
// # of max Cut
int C;

vector<int> cutCands;

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> L >> K >> C;
    cutCands.resize(K+2);
    for ( int ki = 0; ki < K; ki++ ){
        cin >> cutCands[ki];
    }
    cutCands[K] = 0;
    cutCands[K+1] = L;
    sort( cutCands.begin(), cutCands.end());
    cutCands.erase( unique( cutCands.begin(), cutCands.end()), cutCands.end());
    K = cutCands.size() - 1;

    int ans1 = 0;
    int ans2 = 0;
    // Parametric Search
    int l = 1;
    int r = L - 1;
    while ( l <= r ){
        int mid = (r-l)/2 + l;

        int leftMostCut = L;
        int cutCount = 0;
        int rPos = L;
        for ( int i = K-1 ; i >= 0; i-- ){
            int cutPos = cutCands[i];
            int len = rPos - cutPos;
            // cout << "mid\tcutPos\tleftMostCut\tcutCount\trPos\n"
            //                 << mid << "\t" << cutPos << "\t" << leftMostCut << "\t" << cutCount << "\t" << rPos << endl; // DEBUG
            if ( len > mid ){
                rPos = cutCands[i+1];
                if ( rPos - cutPos > mid ){
                    cutCount = INT32_MAX;
                    break;
                }
                leftMostCut = min( leftMostCut, cutCands[i+1] );
                cutCount++;
            }
        }
        if ( cutCount < C ){
            cutCount++;
            leftMostCut = cutCands[1];
        }

        if ( cutCount <= C ) {
            ans1 = mid;
            ans2 = leftMostCut;
            r = mid - 1;
        }
        else {
            l = mid + 1;
        }
    }

    cout << ans1 << " " << ans2;

    return 0;
}