#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_PREFIX = 9;
const int MAX_LEN = 10;

vector<vector<int>> table( MAX_PREFIX+1, vector<int>(MAX_LEN+1, 0 ));
int N;

inline int64_t Get10PowY( int Y )
{
    int64_t rst = 1;
    for ( int i = 1; i <= Y; i++ ){
        rst *= 10;
    }
    return rst;
}
int64_t FindRecursive( int parentPrefix, int parentLen, int leftCount )
{
    if ( parentLen == 1 && leftCount == 1 )
        return 0;
    if (  parentLen == 1 && leftCount != 1 )
        exit(-1);

    int64_t rst = 0;

    int count = 0;
    int len = parentLen-1;
    for ( int64_t prefix = 0; prefix < parentPrefix; prefix++ ){
        if ( (count+table[prefix][len] < leftCount ) ){
            count += table[prefix][len];
        }
        else {
            int64_t child = FindRecursive(prefix, len, leftCount - count );
            // printf( "pP %d, pL %d, tC %d, cP %d, child %d\n", parentPrefix, parentLen, trgCount, prefix, child);
            // printf( "cur prefix val %d\n", prefix*Get10PowY(len-1) );
            rst = prefix*Get10PowY(len-1) + child;
            break;
        }
    }

    return rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    N++;

    // Build Table O(p*l*p);
    for ( int prefix = 0; prefix <= MAX_PREFIX; prefix++ ){
        // len == 1
        table[prefix][1] = 1;
        // len in 2..maxlen
        for ( int len = 2; len <= MAX_LEN; len++ ){
            for ( int prev = 0; prev < prefix; prev++ ){
                table[prefix][len] += table[prev][len-1];
            }
        }
    }

    // for ( int prefix = 0; prefix <= MAX_PREFIX; prefix++ ){ // Debug
    //     for ( int len = 0; len <= MAX_LEN; len++ ){
    //         cout << table[prefix][len] << " ";
    //     } cout << endl;
    // }

    // Search
    int64_t ans = -1;
    int count = 0;
    for ( int len = 1; len <= MAX_LEN && ans == -1; len++ ){
        for ( int64_t prefix = 0; prefix <= MAX_PREFIX && ans == -1; prefix++ ){
            if ( (count+table[prefix][len]) < N ){
                count += table[prefix][len];
            }
            else {
                ans = FindRecursive( prefix, len, N - count );
                ans += prefix*Get10PowY(len-1);
                break;
            }
        }
    }

    cout << ans;
    return 0;
}