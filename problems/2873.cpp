#include <iostream>

using namespace std;

int matrix[1000][1000];
enum ways{
    UP,
    DOWN,
    LEFT,
    RIGHT
};

void trv_row( const int r, const int c ){
    int ri = 0;
    int ci = 0;
    enum ways way = RIGHT;

    matrix[0][0] = 0;
    while ( 1 ){
        if ( (ri+1) == (r-1) && way == RIGHT && matrix[ri+1][ci] > 0 ){
            ri++;
            cout << "D";
        }
        else if ( ri >= 1 && matrix[ri-1][ci] > 0 ){
            ri--;
            cout << "U";
        }
        else if ( way == LEFT && (ci-1) >= 0 && matrix[ri][ci-1] > 0){
            ci--;
            cout << "L";
            if ( ci == 0 ) way = RIGHT;
        }
        else if ( way == RIGHT && (ci+1) < c && matrix[ri][ci+1] > 0){
            ci++;
            cout << "R";
            if ( ci == c - 1 ) way = LEFT;
        }
        else {
            ri++;
            cout << "D";
        }
        matrix[ri][ci] = 0;
        
        if ( ri == (r - 1) && ci == (c - 1) )
            break;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    int r, c;
    cin >> r >> c;
    int r_min = 0;
    int c_min = 1;
    for ( int ri = 0; ri < r; ri++ ){
        for ( int ci = 0; ci < c; ci++ ){
            cin >> matrix[ri][ci];
            if ( (ri+ci)%2 == 1 && matrix[ri][ci] < matrix[r_min][c_min] ){
                r_min = ri;
                c_min = ci;
            }
        }
    }

    if ( r % 2 == 0 && c % 2 == 0 ){
        matrix[r_min][c_min] = 0;
        trv_row( r, c );
    }
    else {
        if ( r % 2 == 0 ){
            for ( int ci = 0; ci < c; ci++ ){
                if ( ci % 2 == 0){
                    for ( int ri = 1; ri < r; ri++ )
                        cout << "D";
                }
                else {
                    for ( int ri = 1; ri < r; ri++ )
                        cout << "U";
                }
                if ( ci < c - 1 )
                    cout << "R";
            }
        }
        else 
            trv_row( r, c );
    }

}