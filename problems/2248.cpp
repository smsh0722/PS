#include <iostream>
#include <vector>

using namespace std;

int64_t N, L, I;

inline int64_t Combination(int n, int r )
{
    if ( r == 0 || r == n)
        return 1;

    int64_t rst = 1;
    
    { // optimize calculation
        int rP = n - r;
        if ( r > rP )
            r = rP;
    }
    
    // Calculate
    int ri = r;
    for ( int i = 0; i < r; i++ ){
        rst *= (n-i);
        while ( ri > 1 && rst % ri == 0 ){
            rst /= ri;
            ri--;
        }
    }
    while ( ri > 1 && rst % ri == 0 ){
        rst /= ri;
        ri--;
    }

    return rst;
}

int64_t CalNumOfCases( int n, int l )
{
    int64_t rst = 0;
    if ( n < l )
        l = n;

    for ( int i = l; i >= 0; i-- ){
        rst += Combination(n, i);
    }
    return rst;
}

int main( void )
{
    cin >> N >> L >> I;
    int ans = 0; // 0000,0000,0000,0000,0000,0000,0000,0000,

    int64_t leftNumOfCase = I;
    int64_t leftNumOfBit = L;
    for ( int l = N; l > 0; l-- ){ // TODO: check end case
        int64_t a = CalNumOfCases(l,leftNumOfBit);
        int64_t b = CalNumOfCases(l-1, leftNumOfBit);
        if ( a >= leftNumOfCase && leftNumOfCase > b ){
            ans |= (1<<(l-1));
            leftNumOfBit--;
            leftNumOfCase -= b;
        }
    }

    for ( int i = N; i > 0; i-- ){
        int mask = 1<<(i-1);
        bool c = ans&mask;
        cout << int(c);
    }
}