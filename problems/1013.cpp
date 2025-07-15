#include <iostream>
#include <vector>
#include <string>
using namespace std;

struct State{
    bool bFinal;
    int trg0;
    int trg1;
};

vector<State> states = {
    State{ false, 1, 3}, // 0
    State{ false, -1, 2}, // 1
    State{ true, 1, 3}, // 2
    State{ false, 4, -1}, // 3
    State{ false, 5, -1}, // 4
    State{ false, 5, 6}, // 5
    State{ true, 1, 7}, // 6
    State{ true, 8, 7}, // 7
    State{ false, 5, 2}, // 8
};

int T;

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    for ( int t = 0; t < T; t++ ){
        string s;
        cin >> s;

        bool bRst = false;
        int stateIdx = 0;
        for ( size_t si = 0; si < s.size(); si++ ){
            //printf("state[%d]\n", stateIdx); // debug
            char c = s[si];
            int nextState = -1;
            if ( c == '0' ){
                nextState = states[stateIdx].trg0;
            }
            else { // c == '1'
                nextState = states[stateIdx].trg1;
            }
            
            if ( nextState == -1 ){
                bRst = false;
                break;
            }
            stateIdx = nextState;
            bRst = states[stateIdx].bFinal;
        }
        //printf("final state[%d]\n", stateIdx); // debug

        if ( bRst == true )
            cout << "YES\n";
        else 
            cout << "NO\n";
    }

    return 0;
}