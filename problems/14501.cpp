#include <iostream>
using namespace std;

int bruteSearch( const int N, const int T[], const int P[], int idx, int sum )
{
    if ( T[idx] + idx - 1 < N ){
        sum += P[idx];
        int max = 0;
        for ( int i = T[idx] + idx; i < N; i++ ){
            int bruteRst = bruteSearch( N, T, P, i, 0 );
            max = max < bruteRst ? bruteRst : max;
        }
        sum += max;
    }  

    return sum;
}

int main( void )
{
    int n;
    cin >> n;
    
    int T[n], P[n];
    int i;
    for ( i = 0; i < n; i++ )
        cin >> T[i] >> P[i];
    
    int max = 0;
    for ( i = 0; i < n; i++ ){
        int bruteRst = bruteSearch( n, T, P, i, 0 );
        max = max < bruteRst ? bruteRst : max;
    }
    cout << max;
}