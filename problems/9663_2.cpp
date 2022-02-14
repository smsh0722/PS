#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int moveR[8] = { 1, -1, 0, 0, 1, -1, -1, 1 };
int moveC[8] = { 0, 0, 1, -1, -1, 1, -1, 1 };
int checkCase( const int pieceNum, vector< vector<bool> >& board, const int r, const int c, const int n );
void push_trg( const int n, const int pos, vector<vector<bool>>& board );

int main( void )
{
    int n;
    cin >> n;

    int count = 0;
    {
        vector< vector<bool> > board( n, vector<bool>(n, false ) ); // -1 불가, 0 빈칸, 1 Qeen

        vector< vector<bool> > save = board;
        for ( int r = 0; r < n; r++ ){
            for ( int c = 0; c < n; c++ ){
                board = save;
                int pos = r * n + c;

                push_trg( n, pos, board );  
                count += checkCase( 1, board, r, c, n );
            }
        }
    }
    cout << count;

    return 0;
}

int checkCase(  const int peiceNum, vector< vector<bool> >& board, const int r, const int c, const int n )
{    
    if ( peiceNum == n ){
        return 1;
    }

    int count = 0;
    {
        vector< vector<bool> > save = board;
        int nextPeiceNum = peiceNum + 1;
        for( int trgR = r; trgR < n; trgR++ ){
            int trgC;
            {
                if ( trgR == r ){
                    trgC = c + 1;
                }
                else {
                    trgC = 0;
                }
            }
            for ( trgC; trgC < n; trgC++ ){
                if ( board[trgR][trgC] == true ){
                    continue;
                }
                else {
                    if ( nextPeiceNum == n ){
                        count++;
                        continue;
                    }
                    else{
                        int pos = trgR * n + trgC;
                        // 상하
                        push_trg( n, pos, board );  
                        count += checkCase( nextPeiceNum, board, trgR, trgC, n );
                    }
                }
                board = save;
            }
        }
    }

    return count;
}

void push_trg( const int n, const int pos, vector<vector<bool>>& board )
{
    const int posR = pos / n;
    const int posC = pos % n;

    for ( int i = 0; i < 8; i++ ){
        int r = moveR[i];
        int c = moveC[i];

        int trgR = posR;
        int trgC = posC;
        while ( true ){
            trgR += r;
            trgC += c;
            if ( trgR >= n || trgR < 0 ){
                break;
            }
            if ( trgC >= n || trgC < 0 ){
                break;
            }

            board[trgR][trgC] = true;
        }
    }
}