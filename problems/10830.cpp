/* smsh0722
 * 10830
 * 행렬 제곱
 * */
#include <iostream>
using namespace std;

void pow_matrix( int** matrix, int size, int64_t B, int** matrix_original );
void mul_matrix( int** m_a, int** m_b, int size );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N;
    int64_t B;
    cin >> N >> B;
    
    int** matrix = new int*[N];
    int** matrix_original = new int*[N];
    for ( int i = 0; i < N; i++ ){
        matrix[i] = new int[N];
        matrix_original[i] = new int[N];
        for ( int j = 0; j < N; j++ ){
            cin >> matrix[i][j];
            matrix_original[i][j] = matrix[i][j];
        }
    }
    
    pow_matrix( matrix, N, B, matrix_original );

    if ( B == 1 ){
        for ( int i = 0; i < N; i++ )
            for ( int j = 0; j < N; j++ )
                matrix[i][j] %= 1000;
    }

    // Print out
    for ( int i = 0; i < N; i++ ){
        for ( int j = 0; j < N; j++ )
            cout << matrix[i][j] << " ";
        cout << "\n";
    }
}

void pow_matrix( int** matrix, int size, int64_t B, int** matrix_original )
{
    if ( B == 1 || B == 0 )
        return;

    pow_matrix( matrix, size, B / 2, matrix_original );
    mul_matrix( matrix, matrix, size );

    if ( B&1 == 1 )
        mul_matrix( matrix, matrix_original, size );

    return;
}

void mul_matrix( int** m_a, int** m_b, int size )
{
    // mxn nxp
    int** new_m = new int*[size];
    for ( int a_r = 0; a_r < size; a_r++ ){
        new_m[a_r] = new int[size];
        for ( int b_c = 0; b_c < size; b_c++ ){
            new_m[a_r][b_c] = 0;
            for ( int a_c = 0; a_c < size; a_c++ ){
                new_m[a_r][b_c] += m_a[a_r][a_c] * m_b[a_c][b_c];
            }
            new_m[a_r][b_c] %= 1000;
        }
    }
    
    for ( int i = 0; i < size; i++ ){
        for ( int j = 0; j < size; j++ )
            m_a[i][j] = new_m[i][j]; // save changed val
        delete[] new_m[i]; // avoid mem leaks
    }
    delete[] new_m; // avoid mem leaks
}