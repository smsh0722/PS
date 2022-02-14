#include <iostream>
#include <string>
using namespace std;

inline int max_ab( int a, int b )
{
    return a > b ? a : b;
}

void lcs( string& s1, string& s2 )
{   
    const int S1_LEN = s1.size();
    const int S2_LEN = s2.size();
    int dp[S1_LEN+1][S2_LEN+1];
    int i, j;

    for ( i = 0; i <= S1_LEN; i++ ){
        for( j = 0; j <= S2_LEN; j++ ){
            if ( i == 0 || j == 0 )
                dp[i][j] = 0;
            else if ( s1.at(i-1) == s2.at(j-1) )
                dp[i][j] = dp[i-1][j-1] + 1;
            else 
                dp[i][j] = max_ab( dp[i-1][j], dp[i][j-1] );
        }
    }
    
    cout << dp[S1_LEN][S2_LEN];
    string sqnc;
    {
        i = S1_LEN;
        j = S2_LEN;
        while ( i > 0 && j > 0 ){
            if ( s1[i-1] == s2[j-1] ){
                sqnc.push_back( s1.at(i-1) );
                i--; j--;
            }
            else if ( dp[i-1][j] > dp[i][j-1] )
                i--;
            else
                j--;
        }
    }
    if ( sqnc.size() > 0 ) cout << "\n";
    for ( string::reverse_iterator rit = sqnc.rbegin(); rit != sqnc.rend(); rit++ ){
        cout << *rit;
    }

}

int main( void )
{
    string s1, s2;
    cin >> s1;
    cin >> s2;
    lcs( s1, s2 );
}
