#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_POW = 50;

// Num of nodes;
int64_t N;
// k tree
int K;
// Num of Queries
int Q;

vector<int64_t> boundMemo(MAX_POW+1, 1);

int GetDepth( int64_t num )
{
    int depth = 0;
    while ( depth <= MAX_POW ){
        if ( num <= boundMemo[depth] )
            break;
        depth++;
    }

    return depth;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> Q;

    // Build i-depth Sum memo
    if ( K != 1 ){
        int64_t curSize = 1;
        for ( int i = 1; i <= MAX_POW; i++ ){
            curSize *= K;
            boundMemo[i] = boundMemo[i-1] + curSize;
            // printf("boud[%d]: %I64d\n", i, boundMemo[i]);
        }
    }
    
    // Answer
    int64_t offset = K-2;
    for ( int q = 0; q < Q; q++ ){
        int64_t a, b;
        int64_t ans = 0;

        cin >> a >> b;
        if ( a > b )
            swap(a, b);
        
        // Answer
        if ( K == 1 ){
            cout << b-a << "\n";
        }
        else {
            int da = GetDepth(a);
            int db = GetDepth(b);
            for ( int diff = db - da; diff > 0; diff-- ){
                ans++;
                b = (b+offset)/K;
            }       

            while ( a != b ){
                a = (a+offset) / K;
                b = (b+offset) / K;
                ans +=2;
            }

            /*
                    1
            2       3      4       5
            6789
            22.23.24.25.
            */
            cout << ans << "\n";
        }
    }

    return 0;
}