/* NOTE:
manacher algorithm
reference: https://www.geeksforgeeks.org/dsa/manachers-algorithm-linear-time-longest-palindromic-substring-part-1/
*/

#include <iostream>
#include <vector>
#include <string>
using namespace std;

string s;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> s;

    string ms = "$";
    for ( size_t si = 0; si < s.length(); si++ ){
        ms += "#";
        ms += s[si]; 
        /* NOTE: 
        ms += "#" + s[si]; 
        로 하면 틀린다.
        */
    }
    ms += "#;";
    const int msLen = ms.length();
    // cout << "ms: " << ms << endl;// DEBUG

    vector<int> radiuses( ms.length(), 0 );
    {
        int l = 0;
        int r = 0;
        for ( int i = 1; i < msLen-1; i++ ){
            if ( i < r ){
                int opposite = l + (r-i);
                radiuses[i] = min( radiuses[opposite], r - i );
            }

            while ( ms[i-radiuses[i]-1] == ms[i+radiuses[i]+1] ){
                radiuses[i]++;
            }

            if( i + radiuses[i] > r ){
                l = i - radiuses[i];
                r = i + radiuses[i];
            }
        }
    }   

    int ans = 1;
    for ( int i = 1; i < msLen; i++ ){
        ans = max(ans, radiuses[i] );
    }
    cout << ans;

    return 0;
}