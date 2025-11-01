#include <iostream>
#include <vector>
#include <string>
using namespace std;

string s1;
string s2;

/* table[s1 idx][s2 idx] = (longest length)
    
s1: ABSADJFLS
s2: ASDFSDF
*/
vector<vector<string>> table;

string max( const string& a, const string& b )
{
    if ( a.length() < b.length() )
        return b;
    return a;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); 

    cin >> s1;
    cin >> s2;
    
    table.resize( s1.length()+1, vector<string>( s2.length()+1, "" ) );
    for ( int s1Idx = s1.length() - 1; s1Idx >= 0; s1Idx-- ){
        for ( int s2Idx = s2.length() -1; s2Idx >= 0; s2Idx-- ){
            if ( s1[s1Idx] == s2[s2Idx] )
                table[s1Idx][s2Idx] = s1[s1Idx] + table[s1Idx+1][s2Idx+1];
            else 
                table[s1Idx][s2Idx] = max( table[s1Idx][s2Idx+1], table[s1Idx+1][s2Idx] );
        }
    }

    // // DEBUG
    // for ( auto c : s2 )
    //     cout << "\t" << c;
    // for ( int r = 0; r <= s1.length(); r++ ){
    //     cout << endl << s1[r] << "\t";
    //     for ( int c = 0; c <= s2.length(); c++ ){
    //         cout << table[r][c] << ",\t";
    //     }
    // }

    cout << table[0][0];

    return 0;
}