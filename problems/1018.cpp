#include <iostream>
using namespace std;

int findB( int r, int c, char** board );
int findW( int r, int c, char** board );

int main( void )
{
    int w, h; // w X h
    cin >> h >> w;

    char** board = new char*[h];
    for ( int i = 0; i < h; i++ ) {
        board[i] = new char[w];
        cin >> board[i];
    }

    int max = 0;
    int caseB, caseW;
    for ( int r = 0; r <= h - 8; r++ ){
        for ( int c = 0; c <= w - 8; c++ ){
            caseB = findB( r, c, board );
            caseW = findW( r, c, board );
            if ( max < caseB ) max = caseB;
            if ( max < caseW ) max = caseW;
        }
    }

    cout << 64 - max << endl;
}

int findB( int r, int c, char** board ){
    int count = 0;
    for ( int i = r; i <= r + 6; i += 2 ){
        for ( int j = c; j <= c + 6; j += 2 ){
            if ( board[i][j] == 'B' ) ++count;
            if ( board[i][j+1] == 'W' ) ++count;
        }
    }
    for ( int i = r + 1; i <= r + 7; i += 2 ){
        for ( int j = c; j <= c + 6; j += 2 ){
            if ( board[i][j] == 'W' ) ++count;
            if ( board[i][j+1] == 'B' ) ++count;
        }
    }
    return count;
}
int findW( int r, int c, char** board ){
    int count = 0;
    for ( int i = r; i <= r + 6; i += 2 ){
        for ( int j = c; j <= c + 6; j += 2 ){
            if ( board[i][j] == 'W' ) ++count;
            if ( board[i][j+1] == 'B' ) ++count;
        }
    }
    for ( int i = r + 1; i <= r + 7; i += 2 ){
        for ( int j = c; j <= c + 6; j += 2 ){
            if ( board[i][j] == 'B' ) ++count;
            if ( board[i][j+1] == 'W' ) ++count;
        }
    }
    return count;
}