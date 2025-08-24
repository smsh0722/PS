#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int NUM_OF_STATES = 10;

struct State{
    int transition[2] = {0,0};
    bool bFinal = false;
    State( int dst1, int dst2, bool b ){
        transition[0] = dst1;
        transition[1] = dst2;
        bFinal = b;
    }
};

State states[NUM_OF_STATES] = {
    State( 1, 2, false ), // 0 // Start State
    State( 9, 3, false ), // 1
    State( 4, 9, false ), // 2
    State( 1, 2, true ), // 3
    State( 5, 9, false ), // 4
    State( 5, 6, false ), // 5
    State( 1, 7, true ), // 6
    State( 8, 7, true ), // 7
    State( 5, 3, false ), // 8
    State( 9, 9, false ), // 9
};

// Num of TestCase
int T;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for ( int t = 0; t < T; t++ ){
        string s;
        cin >> s;

        int state = 0;

        for ( size_t i = 0; i < s.size(); i++ ){
            int symbol = s[i] - '0';
            state = states[state].transition[symbol];
        }
        
        if ( states[state].bFinal == true )
            cout << "YES\n";
        else 
            cout << "NO\n";
    }
    
    return 0;
}