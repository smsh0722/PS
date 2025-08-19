#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_STRING_LEN = 5000;

string s;
vector<int> lps(MAX_STRING_LEN, 0 );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> s;

    int ans = 0;

    for ( size_t l = 0; l < s.size(); l++ ){
        string trg = s.substr(l);
        
        int len = 0;
        size_t i = 1;
        lps[0] = 0;
        while ( i < trg.size() ){
            if ( trg[i] == trg[len] ){
                len++;
                lps[i] = len;
                ans = ans < len ? len : ans;
                i++;
            }
            else {
                if ( len > 0 ){
                    len = lps[len-1];
                }
                else {
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

    cout << ans;

    return 0;
}