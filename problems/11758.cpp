#include <iostream>

using namespace std;

enum direction {
    clockwise = -1,
    straight,
    counterclockwise,
};

int main( void )
{
    int p[3][2]; // point

    for ( int i = 0; i < 3; i++ )
        cin >> p[i][0] >> p[i][1];

    enum direction dir;

    /* linear p1 to p2
     * -by = ax + c
     * ax + by + c = 0
     * */
    int a = p[1][1] - p[0][1]; // y'
    int b = -(p[1][0] - p[0][0]); // -x'

    if ( b != 0 ){
        int c = -( a*p[0][0] + b*p[0][1] );
        int V = a*p[2][0] + b*p[2][1] + c;
        {
            if ( V == 0 )
                dir = straight;
            else if ( V > 0 )
                dir = clockwise;
            else //( V < 0 )
                dir = counterclockwise;
        }
    }
    else {//( b == 0 )
        int v23_x = p[2][0] - p[1][0];
        if ( a > 0 ){
            if ( v23_x > 0 )
                dir = clockwise;
            else if ( v23_x < 0 )
                dir = counterclockwise;
            else //( v23_x == 0 )    
                dir = straight;
        }
        else {//( a < 0 )
            if ( v23_x > 0 )
                dir = counterclockwise;
            else if ( v23_x < 0 )
                dir = clockwise;
            else //( v23_x == 0 )    
                dir = straight;
        }
    }

    cout << dir << "\n";
}