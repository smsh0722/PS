/* smsh0722
 * 2448
 * 별 찍기 - 11
 * */
#include <iostream>
#include <cstring>
using namespace std;

/* Divide and Conquer
 * trgH = target Height
 * trgR = target Row
 * trgC = target Column
 * */
void getPic( char** picture, int trgH, int trgR, int trgC );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N; // # of line (3*2^k), (k=0,1,...,10)
    cin >> N;

    int W = 2 * N - 1;
    
    /* Result Picture
     * [NxW] char Array
     * picture[r][c], r = row, c = column
     * true == '*'
     * false == ' '
     * */
    char** picture;
    picture = new char*[N];
    for ( int i = 0; i < N; i++ ){
        picture[i] = new char[W];
        memset( picture[i], ' ', W );
    }

    getPic( picture, N, 0, W / 2 );

    // print Picture
    for ( int i = 0; i < N; i++ ){
        for ( int j = 0; j < W; j++ )
            cout << picture[i][j];
        cout << "\n";
    }
}   

void getPic( char** picture, int trgH, int trgR, int trgC )
{
    // Base Caes
    if ( trgH == 3 ){
        picture[trgR][trgC] = '*';
        picture[trgR+1][trgC-1] = '*'; picture[trgR+1][trgC+1] = '*';
        for ( int i = 0; i < 5; i++ )
            picture[trgR+2][trgC-2+i] = '*';
        
        return;
    }
    
    // Divide
    trgH /= 2;
    int nextW = trgH * 2 - 1;
    int lC = trgC - ( nextW / 2 + 1 );
    int rC = trgC + ( nextW / 2 + 1 );
    getPic( picture, trgH, trgR, trgC );
    getPic( picture, trgH, trgR + trgH, lC );
    getPic( picture, trgH, trgR + trgH, rC );

    return;
}