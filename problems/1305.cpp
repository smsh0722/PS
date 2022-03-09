/* smsh0722
 * 1305
 * 광고
 * */
#include <iostream>
#include <cstring>
using namespace std;

int main( void )
{
    int L; cin >> L;
    char* board = new char[L+1]; 
    cin >> board;

    int* lps = new int[L];
    lps[0] = 0;
    {
        int len = lps[0];
        int i = 1;
        while ( i < L ){
            if ( board[i] == board[len] ){
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if ( len == 0 ){
                    lps[i] = 0;
                    i++;
                }
                else 
                    len = lps[len-1];
            }
        }
    }

    cout << L - lps[L-1];
    return 0;
}