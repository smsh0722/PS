#include <iostream>
#include <vector>
#include <string>
using namespace std;

string T;
string P;

// Longest Prefix Suffix
vector<int> lps;
vector<int> ans;

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Input
    getline(std::cin, T); // NOTE: getline c++ 사용법 외워두기
    getline(std::cin, P);

    // Resizing LPS vector
    lps.resize( P.size(), 0);

    // Build lps
    {
        size_t len = 0;
        size_t i = 1;
        while ( i < P.size() ){
            if ( P[len] == P[i] ){
                len++;
                lps[i] = len;
                i++;
            }
            else {
                if ( len > 0 ){
                    len = lps[len-1];
                }
                else { // len == 0;
                    lps[i] = 0;
                    i++;
                }
            }
        }
    }

    // Search T
    size_t ti = 0;
    size_t pi = 0;
    while ( ti < T.size() ){
        if ( T[ti] == P[pi] ){
            ti++;
            pi++;
            /* 012345
            T: BABCDE
            P: ABC
            
            ti = 4, pi = 3
            starting idx = ti - pi;

            */
            if ( pi == P.size() ){
                ans.push_back(ti-pi+1);
            }
        }
        else { // T[ti] != P[pi]
            if ( pi > 0 ){
                pi = lps[pi-1];
            }
            else { // pi == 0
                ti++;
            }
        }
    }

    // Answer
    cout << ans.size() << "\n" ;
    for ( size_t i = 0; i < ans.size(); i++ ){
        cout << ans[i] << " ";
    }

    return 0;
}