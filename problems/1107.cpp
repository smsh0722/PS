/* smsh0722
 * 1107
 * 리모컨
 * */
#include <iostream>
#include <string>
using namespace std;

const int INF = 500001; // 500,000
enum condition{ 
    WORKING = 0, 
    NOTWORKING
};

int findMinCase( string N, condition buttons[], int trgSize, string num );

int main( void )
{
    int N, M;
    condition buttons[10] = { WORKING };

    cin >> N;
    cin >> M;
    for ( int i = 0; i < M; i++ ){
        int button;
        cin >> button;
        buttons[button] = NOTWORKING;
    }
    
    int a = abs( N - 100 ); // except numButton
    int b = INF;            // Include numButton
    {
        string N_str = to_string( N );
        int tmp;
        // Case num length 1 ~ 
        for ( int i = 1; i <= N_str.length() + 1; i++ ){
            tmp = findMinCase( N_str, buttons, i, "" );
            b = b > tmp ? tmp : b;
        }
        // Case num 0
        if ( buttons[0] == WORKING ){
            tmp = N - 0 + 1;
            b = b > tmp ? tmp : b;
        }
    }

    cout << (a > b ? b : a) << endl;

    return 0;
}

int findMinCase( string N, condition buttons[], int trgSize, string num )
{   
    // End
    if ( num.length() == trgSize )
        return abs( stoi(N) - stoi(num) ) + trgSize;
    
    // Click more button
    int min = INF;
    for ( int i = 0; i <= 9; i++ ){
        if ( i == 0 && num.length() == 0 )
            continue;
        if ( buttons[i] == WORKING ){
            int tmp = findMinCase( N, buttons, trgSize, num + to_string(i) );
            min = min > tmp ? tmp : min;
        }
    }
    return min;
}