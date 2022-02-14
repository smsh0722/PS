/* 1463 1로 만들기
 * Dynamic Programming
 * smsh0722
 * */
#include <iostream>
using namespace std;

const int INFINITE = 1000000;

int main( void )
{
    int n; cin >> n;
    int arr[n+1]; // 1~n

    /* base case */
    arr[1] = 0;
    arr[2] = 1;
    arr[3] = 1;
    /* make tabulation */
    int a, b, c;
    for ( int i = 4; i <= n; i++ ){
        a = 1 + arr[i-1];
        b = i % 2 == 0 ? 1 + arr[i/2] : INFINITE;
        c = i % 3 == 0 ? 1 + arr[i/3] : INFINITE;
        if ( a <= b && a <= c )
            arr[i] = a;
        else if ( b <= a && b <= c )
            arr[i] = b;
        else if ( c <= a && c <= b )
            arr[i] = c;
    }

    cout << arr[n];
}