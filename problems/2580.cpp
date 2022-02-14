#include <iostream>
#include <vector>
using namespace std;

const int LINESIZE = 9;

bool fillBoard( vector< vector<int> >& board, vector< pair<int, int> >& blankVector );

int main( void )
{
    ios_base::sync_with_stdio(false);

    vector< vector<int> > board( LINESIZE, vector<int>(LINESIZE) );
    vector< pair<int, int> > blankVector; // <r, c>
    for ( int r = 0; r < LINESIZE; r++ ){
        for ( int c = 0; c < LINESIZE; c++ ){
            cin >> board[r][c];
            if ( board[r][c] == 0 ){
                blankVector.push_back( pair<int, int>( r, c ) );
            }
        }
    }
    
    fillBoard( board, blankVector );

    for ( int r = 0; r < LINESIZE; r++ ){
        for ( int c = 0; c < LINESIZE; c++ ){
            cout << board[r][c] << " ";
        }
        cout << "\n";
    }
    return 0;
}

bool fillBoard( vector< vector<int> >& board, vector< pair<int, int> >& blankVector )
{
    return true;
}