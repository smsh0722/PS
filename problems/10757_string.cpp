#include <iostream>
#include <vector>
#include <string>
using namespace std;

string a;
string b;
string ans = "";

inline int CharToInt( char c )
{
    return c - '0';
}

inline char IntToChar( int i )
{
    return i + '0';
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> a;
    cin >> b;

    if ( a.size() < b.size() )
        swap(a, b );
    
    int ai = a.size() -1;
    int bi = b.size() -1;
    int next = 0;
    int cur = 0;
    while ( ai >= 0 ){
        cur = next;
        next = 0;

        cur += CharToInt(a[ai--]);
        if ( bi >= 0 ){
            cur += CharToInt(b[bi--]);
        }

        next = cur / 10;
        cur = cur % 10;

        ans = IntToChar(cur) + ans;
    }
    if ( next > 0 )
        ans = IntToChar(next) + ans;
    
    cout << ans;
    
    return 0;
}