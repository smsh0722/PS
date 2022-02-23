#include <iostream>
using namespace std;

int base_m[2][2] = { {1, 1}, {1, 0} }; // base matrix

int getFib( const int64_t n );
void pow_matrix( int fib_m[2][2], int64_t n );
void mul_matrix( int fib_m[2][2], int m[2][2] );

int main( void )
{
    int64_t n;
    cin >> n;
    
    cout << getFib(n);
}

int getFib( const int64_t n )
{
    // Base case
    if ( n == 0 )
        return 0;
    
    int fib_m[2][2] = { {1, 1}, {1, 0} }; // fibonacci matrix { {fn+1, fn}, {fn, fn-1} }
    pow_matrix( fib_m, n );

    // result
    return fib_m[0][1];
}
void pow_matrix( int fib_m[2][2], int64_t n )
{
    // Base case
    if ( n == 0 || n == 1 )
        return;

    // Calculate
    pow_matrix( fib_m, n / 2 );
    mul_matrix( fib_m, fib_m );

    if ( n % 2 != 0 )
        mul_matrix( fib_m, base_m );
}
void mul_matrix( int fib_m[2][2], int m[2][2] )
{ 
    int64_t a, b, c, d; // { {a, b}, {c, d} }
    a = (int64_t)fib_m[0][0] * m[0][0] + (int64_t)fib_m[0][1] * m[1][0];
    c = (int64_t)fib_m[1][0] * m[0][0] + (int64_t)fib_m[1][1] * m[1][0];
    b = (int64_t)fib_m[0][0] * m[0][1] + (int64_t)fib_m[0][1] * m[1][1];
    d = (int64_t)fib_m[1][0] * m[0][1] + (int64_t)fib_m[1][1] * m[1][1];

    fib_m[0][0] = a % 1000000;
    fib_m[0][1] = b % 1000000;
    fib_m[1][0] = c % 1000000;
    fib_m[1][1] = d % 1000000;
}