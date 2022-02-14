/* 2166 다각형의 면적
 * smsh0722
 * 
 * */
#include <iostream>
#include <cmath>
using namespace std;

int main( void )
{
    int n;
    cin >> n;
    long long int area = 0;
    {
        long long int x0, y0;
        long long int x, y, px, py;
        cin >> x >> y;
        x0 = x; y0 = y;
        for ( int i = 1; i < n; i++ ){
            px = x; py = y;
            cin >> x >> y;
            area += ( px + x ) * ( py - y );
        }
        px = x; py = y;
        area += ( px + x0 ) * ( py - y0 );
    }

    area = llabs(area);
    double result = (double)area / 2;
    result = round( result*10 ) / 10;
    printf("%.1f", result );
    return 0;
}