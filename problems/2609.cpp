#include <iostream>
using namespace std;

int GCD( int a, int b );

int main( void )
{
    int a, b; cin >> a >> b;
    int tGCD;

    tGCD = GCD( a, b );

    cout << tGCD << endl;
    cout << ( a * b / tGCD ) << endl;
}

int GCD( int a, int b ){

    if ( a < b ){
        int temp;
        temp = a;
        a = b;
        b = temp;
    }
    
    if ( b == 0 ) return a;

    return GCD( b, a % b );
}