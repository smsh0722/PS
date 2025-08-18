/* NOTE:
1) N진법 처리는 어떻게할 것인가? 
다음 수은 /N 연산으로, 현재 자리는 % N으로

2) 어떤 수를 Z로 바꿀 것인가?
Greedy-> Z로 바꿀 때의 Gain이 가장 큰 것.
(* 처음에는 각 숫자별로 나타난 크기를 기준으로 Greedy 해서 틀림)
*/
#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
using namespace std;

struct Data{
    char c;
    string sum;
};

const int N_SYSTEM = 36;
int N;
int K;

vector<Data> nums(N_SYSTEM);

inline int CharToInt( char c )
{
    return c >= 'A' ? c-'A'+10 : c-'0';
}

inline char IntToChar( int i )
{
    return i >= 10 ? i-10+'A' : i+'0';
}

inline string AddString( string a, string b )
{
    string rst = "";
    if ( a.size() > b.size() )
        swap(a, b);
    
    int ai = a.size() -1;
    int bi = b.size() -1;
    int next = 0;
    int cur = 0;
    while ( ai >= 0 ){
        cur = next;
        next = 0;

        char ca = a[ai--];
        char cb = b[bi--];
        cur += CharToInt(ca)+CharToInt(cb);

        next = (cur/N_SYSTEM);
        cur = cur % N_SYSTEM;
        rst = IntToChar(cur)+rst;
    }
    while ( bi >= 0 ){
        cur = next;
        next = 0;

        char cb = b[bi--];
        cur += CharToInt(cb);

        next = (cur/N_SYSTEM);
        cur = cur % N_SYSTEM;
        rst = IntToChar(cur)+rst;
    }
    if ( next > 0 )
        rst = IntToChar(next) + rst;

    return rst;
}

inline string MultiplyString( string a, char c )
{
    string rst = "";    

    int ai = a.size() -1;
    int next = 0;
    int cur = 0;
    while ( ai >= 0 ){
        cur = next;
        next = 0;

        cur += CharToInt(a[ai--])*CharToInt(c);
        next = cur / N_SYSTEM;
        cur = cur % N_SYSTEM;
        
        rst = IntToChar(cur) + rst;
    }
    if ( next > 0 )
        rst = IntToChar(next) + rst;
    
    return rst;
}

bool CompareData( const Data& a, const Data& b )
{
    string gainA = MultiplyString( a.sum, IntToChar(CharToInt('Z') - CharToInt(a.c)) );
    string gainB = MultiplyString( b.sum, IntToChar(CharToInt('Z') - CharToInt(b.c)) );
    if ( gainA.size() == gainB.size() ){
        return gainA > gainB;
    }

    return gainA.size() > gainB.size();
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // cout << AddString("AAZZ", ""); return 0;

    // string s = MultiplyString( "AAA", 'Z' );
    // cout << s << endl;
    // for ( size_t i = 0; i < s.size(); i++ ){
    //     cout << CharToInt(s[i]) << " ";
    // } return 0;

    for ( int i = 0; i < N_SYSTEM; i++ ){
        nums[i] = {IntToChar(i), ""};
    }

    cin >> N;
    for ( int i = 0; i < N; i++ ){
        string s;
        cin >> s;
        string x = "1";
        for ( size_t si = 0; si < s.size(); si++ ){
            char c = s[s.size()-1-si];
            int ci = CharToInt(c);
            nums[ci].sum = AddString( nums[ci].sum, x);
            x = x + "0";
        }
    }
    sort( nums.begin(), nums.end(), CompareData );
    
    // // Debug
    // for ( int i = 0; i < N_SYSTEM; i++ ){ 
    //     cout << "For " << nums[i].c << " : " << nums[i].sum << endl;
    // }

    // Greedy
    cin >> K;
    for ( int i = 0; i < N_SYSTEM && K> 0; i++ ){
        if ( nums[i].c == 'Z' )
            continue;
        nums[i].c = 'Z';
        K--;
    }

    string ans = "";
    for ( int i = 0; i < N_SYSTEM; i++ ){
        if ( nums[i].sum.empty() == true )
            continue;
        
        string tmp = MultiplyString( nums[i].sum, nums[i].c );
        ans = AddString( ans, tmp );
    }

    cout << ans;

    return 0;
}