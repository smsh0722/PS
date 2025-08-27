/*
G = (p-c)(p+c)
c^2 = p^2 - G
모든 p를 시도해보며, 매 p마다 수학 공식으로 가능한 c를 O(1)으로 찾을 수 있다.
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int64_t MAX_C = 50001;

int64_t G;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> G;

    bool bAnyAnswer = false;
    for ( int64_t c = 1; c <= MAX_C; c++ ){
        int64_t sqaureC = c*c;
        if ( sqaureC < G )
            continue;
        
        int64_t sqaureP = sqaureC - G;
        if ( sqaureP == 0 )
            continue;
        int64_t p = sqrt(sqaureP);
        if ( p*p == sqaureP ){
            cout << c << "\n";
            // cout << "p: " << p << "\n"; // Debug
            bAnyAnswer = true;
        }
    }

    if ( bAnyAnswer == false )
        cout << -1 << "\n";

    return 0;
}