#include <iostream>
using namespace std;

int gcd( int a, int b );

int main( void )
{
    int n, m; // nCm
    
    cin >> n >> m;
    m = m > n - m ? n - m : m;

    int* mArr = new int[1+m];
    for ( int i = 0; i <= m; i++ ) mArr[i] = i;

    unsigned long long result = 1;
    int gcdN;
    int temp;
    for ( int i = 0; i < m; i++ ){
        temp = n;
        for ( int j = 1; j <= m; j++ ){
            gcdN = gcd( temp, mArr[j] );
            mArr[j] /= gcdN;
            temp /= gcdN;
            if ( temp == 1 ) break;
        }
        result *= temp;
        n--;
    }

    cout << result << "\n";
    return 0;
}

int gcd( int a, int b )
{   
    if ( a < b ){
        int temp = a;
        a = b;
        b = temp;
    }
    if ( b == 0 ) return a;
    else return gcd( b, a % b );
}