#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> seq;
vector<int> maxContinuousLength;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    seq.resize(N);
    for ( int i = 0; i < N; i++ )
        cin >> seq[i];
    
    maxContinuousLength.resize(N+1, 0);
    for ( int i = N-1; i >= 0; i-- ){
        int num = seq[i];

        maxContinuousLength[num] = 1;
        if ( num + 1 <= N ){
            maxContinuousLength[num] += maxContinuousLength[num+1];
        }
        // cout << "num\tmaxcontinuousLength\n"
        //     << num << "\t" << maxContinuousLength[num] << endl;
    }

    int maxLength = 0;
    for ( int i = 1; i <= N; i++ ){
        maxLength = max( maxLength, maxContinuousLength[i] );
    }

    cout << N - maxLength;

    return 0;
}