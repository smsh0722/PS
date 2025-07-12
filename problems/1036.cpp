#include <iostream>
#include <string>
#include <vector>

using namespace std;

int N;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    vector<char[51]> numVec;
    {
        string s;
        for ( int curN = 0; curN < N; curN++ ){
            cin >> s;
            for ( int sIdx = 0; sIdx < s.size(); sIdx++ ){
                int c = s.at(sIdx);
                int powerN = s.size() - sIdx;
                if ( c >= 65 )
                    c -= (65+10);
                else 
                    c -= 48;
                numVec[c][powerN]++;
                int pos = 51 - powerN;
                if ( numVec[c][powerN] >= 36 ){

                }
            }
        }
    }
}
