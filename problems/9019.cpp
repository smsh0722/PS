/* smsh0722
 * 9019
 * DSLR
 * */
#include <iostream>
#include <stdlib.h>
#include <string>
#include <queue>
using namespace std;

struct Case{
    int val;
    string seq;
};

string solve( const int A, const int B );

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);cout.tie(NULL);
    int T;
    cin >> T;

    int A, B;
    for ( int t_i = 1; t_i <= T; t_i++ ){
        cin >> A >> B;

        cout << solve(A,B) << "\n";
    }

    return 0;
}

string solve( const int A, const int B )
{
    bool visited[10001] = {false}; visited[A] = true;
    queue<Case> Q;

    Q.push( Case{A, "" } );
    while ( Q.empty() == false ){
        Case curCase = Q.front(); Q.pop();

        int newVal;
        
        // D
        newVal = (curCase.val * 2) % 10000;
        if ( visited[newVal] == false ){
            if ( newVal == B )
                return (curCase.seq + "D");

            visited[newVal] = true;
            Q.push( Case{newVal, curCase.seq + "D"} );
        }

        // S        
        newVal = curCase.val - 1 < 0 ? 9999 : curCase.val - 1;
        if ( visited[newVal] == false ){            
            if ( newVal == B )
                return ( curCase.seq + "S" );

            visited[newVal] = true;
            Q.push( Case{newVal, curCase.seq + "S"} );
        }

        // L
        newVal = (curCase.val * 10 ) % 10000 + curCase.val / 1000;
        if ( visited[newVal] == false ){
            if ( newVal == B )
                return ( curCase.seq + "L" );

            visited[newVal] = true;
            Q.push( Case{newVal, curCase.seq + "L"} );
        }

        // R
        newVal = (curCase.val / 10 ) + (curCase.val % 10)*1000;
        if ( visited[newVal] == false ){
            if ( newVal == B )
                return ( curCase.seq + "R" );
            
            visited[newVal] = true;
            Q.push( Case{newVal, curCase.seq + "R"} );
        }
    }

    return "NA"; // error
}