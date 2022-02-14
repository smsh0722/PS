#include <iostream>
#include <cstring>
using namespace std;

int gcd( int a, int b );
void aXb( char* a, int b );

int main( void )
{
    ios_base::sync_with_stdio(false);

    int n, m; // nCm
    cin >> n >> m;
    m = m > n - m ? n - m : m;

    int* mArr = new int[1+m];
    for ( int i = 0; i <= m; i++ ) mArr[i] = i;

    char result[200]; memset( result, '0', 200 );
    result[0] = '1';
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
        if ( temp != 1 ) aXb( result, temp );
        n--;
    }

    bool state = false;
    for ( int i = 199; i >= 0; i-- ){
        if ( state == false && result[i] != '0' ) state = true;
        if ( state ) cout << result[i];
    }

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

void aXb( char* a, int b )
{
    char temp[200]; memset( temp, '0', 200 );
    char temp2[200]; memset( temp2, '0', 200 );

    int more = 0;
    int unit = b % 10;
    for ( int i = 0; i < 200; i++ ){
        temp[i] = ( ( a[i] -'0' ) * unit + more ) % 10 + '0';
        more = ( ( a[i] -'0' ) * unit + more ) / 10;
    } 

    b /= 10;
    more = 0;
    if ( b > 0 ){
        for ( int i = 0; i < 199; i++ ){
            temp2[i+1] = ( ( a[i] -'0' ) * b + more ) % 10 + '0';
            more = ( ( a[i] -'0' ) * b + more ) / 10;
        } 
    }

    more = 0;
    for ( int i = 0; i < 200; i++ ){
        a[i] = ( ( temp[i] - '0' ) + ( temp2[i] - '0' ) + more ) % 10 + '0';
        more = ( ( temp[i] - '0' ) + ( temp2[i] - '0' ) + more ) / 10;
    }
}