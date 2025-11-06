/* NOTE:
간단해 보였는데 생각보다 더 살펴봐야했던 문제이다.
아무리 쉬워보여도 되도록 Naive한 접근부터 눈으로 살펴보고 코드로 넘어가자.

SOL) 4DP
*/
#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 50;
const int MAX_M = 50;
const int MAX_ARCADE = 50;
const int DIVISOR = 1000007;

// NxM world
int N, M;
// # of arcades
int C;

int arcades[MAX_N][MAX_M] = {0};
// table[r][c][prev Arcade][count] = count
int table[MAX_N][MAX_M][MAX_ARCADE+1][MAX_ARCADE+1] = {0};

int answers[MAX_ARCADE+1] = {0};

inline void Add( int& a, int& b )
{
    a = (a+b)%DIVISOR;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M >> C;
    for ( int ci = 1; ci <= C; ci++ ){
        int r, c;
        cin >> r >> c;
        r--;c--;

        arcades[r][c] = ci;
    }

    table[0][0][arcades[0][0]][int(arcades[0][0] > 0)] = 1;
    for ( int d = 1; d <= (N+M-2); d++ ){
        for ( int r = 0; r < N; r++ ){
            int c = d - r;
            if ( c >= M )
                continue;
            if ( c < 0 )
                break;
        
            int arcade = arcades[r][c];
            if ( arcade == 0 ){
                for ( int prev = 0; prev <= C; prev++ ){
                    for ( int count = 0; count <= prev; count++ ){
                        if ( r > 0)
                            Add(table[r][c][prev][count], table[r-1][c][prev][count]);
                        if ( c > 0 )
                            Add(table[r][c][prev][count], table[r][c-1][prev][count]);
                    }
                }
            }
            else {
                for ( int prev = 0; prev < arcade; prev++ ){
                    for ( int count = 1; count <= arcade; count++ ){
                        if ( r > 0 )
                            Add(table[r][c][arcade][count], table[r-1][c][prev][count-1]);
                        if ( c > 0 )
                            Add(table[r][c][arcade][count], table[r][c-1][prev][count-1]);
                    }
                }
            }
        }
    }

    for ( int arcade = 0; arcade <= C; arcade++ ){
        for ( int count = 0; count <= C; count++ ){
            Add(answers[count], table[N-1][M-1][arcade][count]);
        }
    }

    for ( int count = 0; count <= C; count++ )
        cout << answers[count] << " ";

    return 0;
}