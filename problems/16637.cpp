/* smsh0722
 * 16637
 * 괄호 추가하기
 * */
#include<iostream>
using namespace std;

int solve( int* operand_arr, char* operator_arr, int bracket_flag, const int SIZE, int opt_idx, bool prev_bracket );
int calculate( int* operand_arr, char* operator_arr, int bracket_flag, const int SIZE );
inline int math( int a, int b, char opt );

int main( void )
{
    int n;
    cin >> n;

    int size = n / 2;
    int* operand_arr = new int[n+1];
    char* operator_arr = new char[n];
    int bracket_flag = 0; // bitmasking
    // Input
    for ( int i = 0; i < n; i++ ){
        if ( (i & 1) == 1 )
            cin >> operator_arr[i/2];
        else 
            cin >> operand_arr[i/2];
    }

    cout << solve( operand_arr, operator_arr, bracket_flag, size, 0, false );
    
    return 0;
}

int solve( int* operand_arr, char* operator_arr, int bracket_flag, const int SIZE, int opt_idx, bool prev_bracket )
{
    if ( opt_idx == SIZE )
        return calculate( operand_arr, operator_arr, bracket_flag, SIZE );

    // No change
    int max = solve( operand_arr, operator_arr, bracket_flag, SIZE, opt_idx+1, false );
    
    if ( prev_bracket == false ){
        int tmp = solve( operand_arr, operator_arr, bracket_flag|(1<<opt_idx), SIZE, opt_idx+1, true );
        max = max < tmp ? tmp : max;
    }
    
    return max;
}
int calculate( int* operand_arr, char* operator_arr, int bracket_flag, const int SIZE )
{
    int a = operand_arr[0];
    for ( int opt_i = 0; opt_i < SIZE; opt_i++ ){
        int b;
        if ( opt_i + 1 < SIZE && (bracket_flag&(1<<(opt_i+1))) != 0 ){
            b = math( operand_arr[opt_i+1], operand_arr[opt_i+2], operator_arr[opt_i+1] );
            a = math( a, b, operator_arr[opt_i] );
            opt_i++;
        }
        else {
            b = operand_arr[opt_i+1];
            a = math( a, b, operator_arr[opt_i] );
        }
    }
    return a;
}
inline int math( int a, int b, char opt )
{
    if ( opt == '+' )
        return a + b;
    else if ( opt == '-' )
        return a - b;
    else // ( operator == '*' )
        return a * b;
}