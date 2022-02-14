#include <iostream>
#include <string>
using namespace std;

inline int max_ab( int a, int b )
{
    return a > b ? a : b;
}

void lcs( string& s1, string& s2, string& s3 )
{   
    const int S1_LEN = s1.size();
    const int S2_LEN = s2.size();
    const int S3_LEN = s3.size();
    int dp[S1_LEN+1][S2_LEN+1][S3_LEN+1];
    int i, j, k;

    for ( i = 0; i <= S1_LEN; i++ ){
        for( j = 0; j <= S2_LEN; j++ ){
            for ( k = 0; k <= S3_LEN; k++ ){
                if ( i == 0 || j == 0 || k == 0 )
                    dp[i][j][k] = 0;
                else if ( s1.at(i-1) == s2.at(j-1) && s2.at(j-1) == s3.at(k-1) )
                    dp[i][j][k] = dp[i-1][j-1][k-1] + 1;
                else 
                    dp[i][j][k] = max_ab( dp[i-1][j][k], max_ab( dp[i][j-1][k], dp[i][j][k-1] ) );
            }
        }
    }
    
    cout << dp[S1_LEN][S2_LEN][S3_LEN];
}

int main( void )
{
    string s1, s2, s3;
    cin >> s1;
    cin >> s2;
    cin >> s3;
    lcs( s1, s2, s3 );
}
