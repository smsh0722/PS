#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 100000;
int N;

/*
idx    0 1 2 .. N-1
seq    1 1 3 ... 5
maxR   0 3 4 ... N-1
*/
vector<int> seq(MAX_N);
vector<int> maxR(MAX_N);
vector<int> leftMostApear; // [num] : left most appear idx

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    
    for ( int i = 0; i < N;i++ ){
        cin >> seq[i];
    }

    leftMostApear.resize(N+1, N);
    leftMostApear[seq[N-1]] = N-1;
    maxR[N-1] = N-1;
    for ( int i = N-2; i >= 0; i-- ){
        int num = seq[i];
        maxR[i] = min(maxR[i+1], leftMostApear[num]-1);
        leftMostApear[num] = i;
    }

    int64_t rst = 0;
    for( int i = 0; i < N; i++ ){
        // printf( "maxR[%d]: %d\n", i, maxR[i]);//Debug
        rst += (maxR[i] - i + 1);
    }

    cout << rst;

    return 0;
}