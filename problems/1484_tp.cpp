/* NOTE:
two_pointer로도 생각할 수 있다.
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
    int64_t l = 1; 
    int64_t r = 1;
    while ( l <= MAX_C && r <= MAX_C ){
        int64_t rst = (r-l) * (r+l);
        if ( rst == G ){
            cout << r << "\n";
            bAnyAnswer = true;
            r++;
        }
        else if ( rst < G ){
            r++;
        }
        else { // rst > G
            l++;
        }
    }

    if ( bAnyAnswer == false )
        cout << -1 << "\n";

    return 0;
}