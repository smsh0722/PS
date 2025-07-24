#include <iostream>
#include <string>
using namespace std;

string s;
string t;
string sr;
int countBInS = 0;
int countBInT = 0;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> s;
    cin >> t;

    // Find direction
    for ( size_t i = 0; i < s.size(); i++ ){
        if ( s.at(i) == 'B')
            countBInS++;
    }
    for ( size_t i = 0; i < t.size(); i++ ){
        if ( t.at(i) == 'B')
            countBInT++;
    }
    const bool bRight = (countBInT - countBInS)%2==0? true : false;
    if ( bRight == false ){
        string tmp = "";
        for ( size_t i = 0; i < s.size(); i++ ){
            tmp = s.at(i) + tmp;
        }
        sr = tmp;
    }

    // Solve
    bool bAvailable = false;
    for ( int sPoint = 0; sPoint < t.size(); sPoint++ ){
        // check l to r
        int l = sPoint;
        int r = sPoint;
        bool bSPoint = true;
        while ( r-l+1 <= s.size() && bSPoint == true ){
            if ( r >= t.size() || l < 0 ){
                bSPoint = false;
                break;
            }

            if ( bRight == true ){
                bSPoint = s.at(r-l) == t.at(r);
                r++;
            }
            else {
                bSPoint = s.at(r-l) == t.at(l);
                l--;
            }
        }
        if ( bSPoint == false )
            continue;

        // printf("sl: %d, sr: %d, bRight: %d\n", l, r, bRight ); // Debug
        // Operation
        string tmp = "";
        if( bRight == true )
            tmp = s;
        else
            tmp = sr;

        bool bSearchRight = bRight;
        while ( l >= 0 && r < t.size() ){
            if ( bSearchRight == true ){
                if( t.at(r) == 'A'){
                    r++;
                    tmp = tmp + "A";
                }
                else {
                    l--;
                    tmp = tmp + "B";
                    bSearchRight = false;
                }
            }
            else {
                if ( t.at(l) == 'A' ){
                    l--;
                    tmp = "A" + tmp;
                }
                else {
                    r++;
                    tmp = "B" + tmp;
                    bSearchRight = true;
                }
            }
        }
        // cout << "tmp: " << tmp << endl; // Debug

        if ( tmp == t ){
            bAvailable = true;
            break;
        }
    }

    cout << int(bAvailable);

    return 0;
}