/* NOTE:
paremetric search, 틀림

시도힐 길이 M은 logL 개 존재.
길이 M이 가능한 중심점 찾기 위해선(L-M)개 조사. 각 조사에서 M길이 조사하므로,
O((L-M)*M*logL)로 시간 초과.

*) (L-M)인데 L/M으로 계산해서 시간 복잡도 잘못 계산해서 틀림.
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

string s;

inline bool IsPalindrome( int si, int l )
{
    bool rst = true;

    int ei = si + l -1;

    int li = si;
    int ri = ei;
    while ( li <= ri){
        // cout << "li\tri\n"
        //     << li << "\t" << ri << endl; // DEBUG
        if ( s[li] != s[ri] ){
            rst = false;
            break;
        }

        li++;
        ri--;
    }

    // cout << "[si\tl\trst]\n"
    //     << si << "\t" << l << "\t" <<  rst <<  endl; // DEBUG

    return rst;
}

int ParemetricSearch( vector<int>& mid )
{
    int ans = 1;

    int li = 0;
    int ri = mid.size() - 1;
    while ( li <= ri ){
        int mi = (ri-li)/2 + li;
        int m = mid[mi];

        bool bExistPalindrome = false;
        for ( int si = 0; si <= int(s.length()) - m; si++ ){
            bExistPalindrome |= IsPalindrome( si, m );
        }

        if ( bExistPalindrome == true ){ // 길이 늘려야함.
            li = mi + 1;
            ans = m; // 최소 mid까진 팰린드롬 존재
        }
        else { // bExistPalindrome == false, 길이 줄여야함.
            ri = mi - 1;
        }
    }

    return ans;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> s;

    int ans = 1;

    // Parametric Search
    vector<int> evenMid(s.length()/2);
    vector<int> oddMid(s.length()/2+s.length()%2);
    for ( size_t i = 0; i < s.length()/2; i++ ){
        evenMid[i] = (i+1)*2;
    }
    for ( size_t i = 0; i < s.length()/2 + s.length()%2; i++ ){
        oddMid[i] = i*2+1;
    }

    ans = max( ans, ParemetricSearch(evenMid) );
    ans = max( ans, ParemetricSearch(oddMid) );

    // Answer
    cout << ans;

    return 0;
}