// Fail code
#include <iostream>
#include <list>
using namespace std;

int facAB( int a, int b );
int gcd( int a, int b ){
    if ( b == 0 ) return a;
    else return gcd( b, a % b );
}

int main( void )
{
    int tileA, tileB; // A 1x2, B 2x1
    int n;            // target 2xn tile
    int count = 0;
    
    cin >> n;
    tileA = n; tileB = 0;
    while ( tileA >= 0 ){
        count += facAB( tileA, tileB );
        
        tileB += 1;
        tileA -= 2;
    }

    cout << count << endl;
}

int facAB( int a, int b ){
    int c = a + b; // c! / (a! * b!)
    int temp;
    if ( a < b ){
        temp = b;
        b = a;
        a = temp;
    }

    if ( b == 0 ) return 1;
    
    list<int> arr;
    for ( int i = 1; i <= b; i++ ) arr.push_back(i);

    unsigned int result = 1;
    while ( c > a ){
        temp = c;
        for ( auto it = arr.begin(); it != arr.end(); it++ ){
            if ( temp % ( *it ) == 0 ){
                temp /= *it;
                it = arr.erase( it );
                it--;
            }
            else {
                temp /= gcd( temp, *it );
            }
        }
        result = result * temp;
        c--;
    }
    return result;
}