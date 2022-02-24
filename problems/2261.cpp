/* smsh0722
 * 2261
 * 가장 가까운 두 점
 * */
#include <iostream>
#include <stdlib.h>
using namespace std;

const int MAXDIST = 800000000; // 800,000,000
const int ARRSIZE = 100000;
struct point {
    int x, y;
};

int myCompX( const void* ap, const void* bp );
int myCompY( const void* ap, const void* bp );
int getClosest( point points[], const int n );
int bruteClosest( point points[], const int n );
int borderClosest( point borderPoints[], const int n, const int d );
int dist( point a, point b );

int main( void )
{
    point points[ARRSIZE];
    int n;
    
    cin >> n;
    
    for ( int i = 0; i < n; i++ )
        cin >> points[i].x >> points[i].y;

    qsort( points, n, sizeof(point), myCompX );

    cout << getClosest( points, n );

    return 0;
}

int myCompX( const void* ap, const void* bp )
{
    point a = *(point*)ap;
    point b = *(point*)bp;
    return a.x - b.x;
}
int myCompY( const void* ap, const void* bp )
{
    point a = *(point*)ap;
    point b = *(point*)bp;
    return a.y - b.y;
}
int getClosest( point points[], const int n )
{
    // Base Case
    if ( n < 4 )
        return bruteClosest( points, n );
    
    // Divide
    int mid = n / 2;
    int dl = getClosest( points, mid );
    int dr = getClosest( points + mid, n - mid );

    // Combine
    int d = dl < dr ? dl : dr;
    
    point borderPoints[n];
    int count = 0;
    for ( int i = 0; i < n; i++ ){
        if ( ( (points+i)->x - points[mid].x )*( (points+i)->x - points[mid].x ) < d )
            borderPoints[count++] = points[i];
    }

    int db = borderClosest( borderPoints, count, d );
    
    d = d > db ? db : d;
    return d;
}
int bruteClosest( point points[], const int n )
{
    int a = dist( *points, *(points + 1) );
    if ( n == 2 )
        return a;

    int min = a;
    int b = dist( *points, *(points + 2) );
    int c = dist( *(points + 1), *(points + 2) );
    
    min = min > b ? b : min;
    min = min > c ? c : min;
    
    return min;
}
int borderClosest( point borderPoints[], const int n, const int d )
{
    qsort( borderPoints, n, sizeof(point), myCompY );

    int min = d;
    for ( int i = 0; i < n; i++ ){
        for ( int j = i + 1; (j < n )&&( ( borderPoints[i].y - borderPoints[j].y )*( borderPoints[i].y - borderPoints[j].y ) < min ); j++ ){
            int d = dist( borderPoints[i], borderPoints[j] );
            min = min > d ? d : min;            
        }
    }
    return min;
}
int dist( point a, point b )
{
    return (a.x - b.x)*( a.x - b.x) + (a.y - b.y)*(a.y - b.y);
}