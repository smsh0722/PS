/* smsh0722
 * 1027
 * 고층 건물
 * */
#include <iostream>
#include <cstring>
using namespace std;

/* Compare Gradient
 * return true, if A < B
 * */
bool compareG( int ay, int ax, int by, int bx );

int main( void )
{
    int N;
    cin >> N;
    
    int* buildings;
    // Input Buildings
    {
        buildings = new int[N];
        for ( int i = 0; i < N; i++ )
            cin >> buildings[i];
    }

    int* numOfVisible;
    // Solve
    {
        numOfVisible = new int[N];
        memset( numOfVisible, 0, sizeof(int)*N );

        for ( int i = 0; i < N; i++ ){
            /* Gradient == ( y / x ) */
            int maxY, maxX;

            // left side
            maxY = maxX = 0;
            for ( int dst = i - 1; dst >= 0; dst-- ){
                int curY, curX;
                curY = buildings[dst] - buildings[i];
                curX = -(dst - i);
                if ( compareG( maxY, maxX, curY, curX ) == true ){
                    maxY = curY;
                    maxX = curX;
                    numOfVisible[i]++;
                }
            }

            // right side
            maxY = maxX = 0;
            for ( int dst = i + 1; dst < N; dst++ ){
                int curY, curX;
                curY = buildings[dst] - buildings[i];
                curX = dst - i;
                if ( compareG( maxY, maxX, curY, curX ) == true ){
                    maxY = curY;
                    maxX = curX;
                    numOfVisible[i]++;
                }
            }
        }
    }

    // Print Answer
    {
        int max = -1;
        for ( int i = 0; i < N; i++ )
            max = max > numOfVisible[i] ? max : numOfVisible[i];
        cout << max;
    }

    return 0;
}

bool compareG( int ay, int ax, int by, int bx )
{
    if ( ax == 0 )
        return true;
    /* compare (ay*bx / ax*bx), (by*ax / ax*bx ) */
    int64_t ay_bx = int64_t(ay) * bx;
    int64_t by_ax = int64_t(by) * ax;
    
    return ay_bx < by_ax;
}