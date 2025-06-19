#include <iostream>
#include <vector>
using namespace std;

int N; 

int aBlock = 0; // -1 block
int bBlock = 0; // 0 block
int cBlock = 0; // 1 block

void SolveBlock( int** mat, int rs, int cs, int range);
bool TestBlock( int** mat, int rs, int re, int cs, int ce );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int** mat;

    cin >> N;

    mat = new int*[N];
    for ( int i = 0; i < N; i++ ){
        mat[i] = new int[N];
        
        for ( int j = 0; j < N; j++ )
            cin >> mat[i][j];
    }

    SolveBlock( mat, 0, 0, N );

    cout << aBlock << endl 
         << bBlock << endl
         << cBlock << endl;

    return 0;
}

void SolveBlock( int** mat, int rs, int cs, int range )
{
    bool testRst = TestBlock(mat, rs, rs + range, cs, cs + range);

    if ( testRst == false )
    {
        int dividedRange = range / 3; // 9 / 3 = 3
        
        for ( int i = 0; i < 3; i++ ){
            for ( int j = 0; j < 3; j++ ){
                SolveBlock(mat
                        , rs + dividedRange*i
                        , cs + dividedRange*j
                        , dividedRange
                    );
            }
        }
    }
}

bool TestBlock( int** mat, int rs, int re, int cs, int ce )
{
    int firstNum = mat[rs][cs];
    //cout << "test block" << endl; // DEBUG
    for ( int r = rs; r < re; r++ )
    {
        for ( int c = cs; c < ce; c++ ){
            //cout << mat[r][c]; // Deubg
            if ( firstNum != mat[r][c] ){
              //  cout << "devide!" << endl; // Debug
                return false;
            }
        }
        //cout << endl; // Debug
    }

    if ( firstNum == -1 )
        aBlock++;
    else if ( firstNum == 0 )
        bBlock++;
    else // firstNum == 1
        cBlock++;
    
    return true;
}