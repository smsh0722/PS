#include <iostream>
#include <cmath>
using namespace std;

void drawZ( int p, int row, int column ); // 2^p
unsigned int count = 0;
int n, r, c;


int main( void )
{
    cin >> n >> r >> c;

    drawZ( n, 0, 0 );
    return 0;
}

void drawZ( int p, int row, int column )
{
    if ( p == 0 ){
        if ( row == r && column == c ) cout << count;
        return;
    }
    else {
        unsigned int n = pow( 2, p - 1 );
        if ( ( r < row + n )&&( c < column + n ) ){
            return drawZ( p - 1, row, column );
        }
        else if ( ( r < row + n )&&( c >= column + n ) ){
            count += n * n;
            return drawZ( p - 1, row, column + n );
        }
        else if ( ( r >= row + n )&&( c < column + n ) ){
            count += 2 * ( n * n );
            return drawZ( p - 1, row + n, column );
        }
        else { // ( r >= row + n )&&( c >= column + n )
            count += 3 * ( n * n );
            return drawZ( p - 1, row + n, column + n );
        }

        /*
        drawZ( p - 1, row, column );            // 2
        drawZ( p - 1, row, column + n );        // 1
        drawZ( p - 1, row + n, column );        // 3
        drawZ( p - 1, row + n, column + n );    // 4
        */
    }
}