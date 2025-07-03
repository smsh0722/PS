#include <iostream>
#include <vector>

using namespace std;

/*
R = N1 - Q1*D
  = N2 - Q2*D
D(Q1-Q2) = N1 - N2
maxD = N1-N2
*/

const int MAX_N = 1000;
int n;

int gcdRecursive( int a, int b)
{
    /* a, b
    a = b*p + q
    b = q*p + q'
    .
    .
    */

    int q = a % b;
    if ( q == 0 ) return b;
    else 
        return gcdRecursive( b, q);
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    vector<int> numVec(MAX_N, 0);

    cin >> n;
    for ( int i = 0; i < n; i++ )
        cin >> numVec[i];

    int gcd = 0;
    for ( int i = 0; i < n-1; i++ ){
        int diff = numVec[i+1] - numVec[i];
        diff = diff > 0 ? diff : -diff;
        if ( diff == 0 )
            continue;
        if ( gcd == 0 )
            gcd = diff;
        else 
            gcd  = gcdRecursive( gcd , diff );
    }

    cout << gcd;
}