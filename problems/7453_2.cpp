#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_N = 4000;
const int NUM_OF_ARR = 4;

int N;
vector<vector<int>> arr(NUM_OF_ARR, vector<int>(MAX_N,0)); // [arr:a,b,c,d][idx]
vector<int> sumAB;
vector<int> sumCD;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); 

    cin >> N;
    for ( int i = 0; i < N; i++ ){
        cin >> arr[0][i]
            >> arr[1][i]
            >> arr[2][i]
            >> arr[3][i];
    }

    sumAB.resize(N*N,0);
    sumCD.resize(N*N,0);
    for ( int i = 0; i < N; i++ ){
        for ( int j = 0; j < N; j++ ){
            sumAB[i*N+j] = arr[0][i] + arr[1][j];
            sumCD[i*N+j] = arr[2][i] + arr[3][j];
        }
    }
    sort(sumAB.begin(), sumAB.end() );
    sort(sumCD.begin(), sumCD.end() );

    for ( int i = 0; i < N*N; i++ ){
        printf("sumAB: %d, \t sumCD: %d\n", sumAB[i], sumCD[i]);
    }
    int64_t ans = 0;
    int l = 0;
    int r = N*N-1;
    while ( l < N*N && r >= 0 ){
        int lup = upper_bound(sumAB.begin(), sumAB.end(), sumAB[l] ) - sumAB.begin() - 1;
        int rlow = lower_bound(sumCD.begin(), sumCD.end(), sumCD[r] ) - sumCD.begin(); 
        printf("l, lup, r, rlow, sab, scd: %d, %d, %d, %d, %d, %d\n", l, lup, r, rlow, sumAB[l], sumCD[r]);

        if ( sumAB[l] + sumCD[r] == 0){
            ans += int64_t(lup-l+1) * int64_t(r - rlow + 1);
            if ( r > 0 )
                r = rlow - 1;
            else 
                l = lup + 1;
        }
        else if ( sumAB[l] + sumCD[r] > 0 ){
            r = rlow - 1;
        }   
        else { // sum < 0
            l = lup + 1;                
        }
    }

    cout << ans;

    return 0;
}