#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int checkCase( const int row, const int& n, vector<int>& c2r );
bool diagonalCheck( const int r, const int c, const vector<int>& c2r, const int& SIZE );

int main( void )
{
    int n;
    cin >> n;

    int count = 0;
    {
        const int HALF = n / 2;
        for ( int c = 0; c < HALF; c++ ){
            vector< int > c2r(n , -1); // column, row
            c2r[c] = 0;
            count += checkCase( 0, n, c2r );
        }
        count *= 2;
        if ( n > 2 && n % 2 == 1 ){
            vector<int> c2r(n,-1);
            c2r[n/2] = 0;
            count += checkCase( 0, n, c2r );
        }
        if ( n == 1 ){
            count = 1;
        }
    }
    cout << count;

    return 0;
}

int checkCase( const int r, const int& n, vector<int>& c2r )
{    
    if ( r == n - 1 ){
        return 1;
    }
    else {
        int count = 0;
        {
            const int trgR = r + 1;
            vector<int> save = c2r;
            for ( int trgC = 0; trgC < n; trgC++ ){
                if ( c2r[trgC] == -1 ){
                    if ( diagonalCheck( trgR, trgC, c2r, n ) == true ){
                        c2r[trgC] = trgR;
                        count += checkCase( trgR, n, c2r );
                        c2r = save;
                    }
                }
            }
        }

        return count;
    }
}

inline void myAbs( int& a ) 
{
     a = a < 0 ? -a : a;
}
bool diagonalCheck( const int r, const int c, const vector<int>& c2r, const int& SIZE )
{
    bool flag = true;
    for ( int qC = 0; qC < SIZE; qC++ ){
        int qR = c2r[qC];
        if ( qR == -1 ){
            continue;
        }

        int cSub = c - qC;
        myAbs( cSub );

        int rSub = r - qR;
        myAbs( rSub );
        
        if ( cSub == rSub ){
            flag = false;
            break;
        }
    }
    return flag;
}