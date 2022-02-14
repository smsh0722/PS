#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int checkCase( const vector< vector<bool> >& allCase, const int n );
void push_trg( const int n, const int pos, const int moveR, const int moveC, vector<vector<bool>>& trgPos );

int main( void )
{
    int n;
    cin >> n;

    int result;
    {
        vector< vector<bool> > allCase;
        {
            const int SIZE = n * n;
            vector< bool > aCase( SIZE - n, false );
            aCase.insert( aCase.end(), n, true );
            do {
                allCase.push_back( aCase );
            } while ( next_permutation( aCase.begin(), aCase.end() ) );
        }
        
        result = checkCase( allCase, n );
    }
    cout << result;

    return 0;
}

int checkCase( const vector< vector<bool> >& allCase, const int n )
{
    const int SIZE = n * n;
    const int CASESIZE = allCase.size();

    int count = 0;
    for ( int caseIdx = 0; caseIdx < CASESIZE; caseIdx++ ){
        bool caseFlag = true;
        {
            vector< int > qPos;
            for ( int i = 0; i < SIZE; i++ ){
                if ( allCase[caseIdx][i] == true ){
                    qPos.push_back(i);
                }
            }

            for ( int idx = 0; idx < n; idx++ ){
                int pos = qPos[idx];
                vector< vector<bool> > trgPos( n, vector<bool>( n, false ) );
                {
                    // 상하
                    push_trg( n, pos, 1, 0, trgPos );  
                    push_trg( n, pos, -1, 0, trgPos );
                    // 좌우
                    push_trg( n, pos, 0, 1, trgPos );
                    push_trg( n, pos, 0, -1, trgPos );
                    // 7시 1시
                    push_trg( n, pos, 1, -1, trgPos );
                    push_trg( n, pos, -1, 1, trgPos );
                    // 11시 5시
                    push_trg( n, pos, -1, -1, trgPos ); 
                    push_trg( n, pos, 1, 1, trgPos );
                }

                for ( int i = 0; i < n; i++ ){
                    if ( pos != qPos[i] ){
                        int r = qPos[i] / n;
                        int c = qPos[i] % n;
                        if ( trgPos[r][c] == true ){
                            caseFlag = false;
                            break;
                        }
                    }
                }

                if ( caseFlag == false ){
                    break;
                }
            }
        }
        if ( caseFlag == true ){
            count++;
        }
    }

    return count;
}

void push_trg( const int n, const int pos, const int moveR, const int moveC, vector<vector<bool>>& trgPos )
{
    const int posR = pos / n;
    const int posC = pos % n;

    int trgR = posR;
    int trgC = posC;
    while ( true ){
        trgR += moveR;
        trgC += moveC;
        if ( trgR >= n || trgR < 0 ){
            break;
        }
        if ( trgC >= n || trgC < 0 ){
            break;
        }

        trgPos[trgR][trgC] = true;
    }
}