/*
Naive하게 나열해놓은 다음. 패턴 찾으려고 노력하기!
*/
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int  T;

inline int64_t GetSeqSum( int length )
{
    int64_t sum = ( 1 + length ) * length / 2;
    return sum;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> T;
    int64_t trg;
    for ( int t = 0; t < T; t++ ){
        cin >> trg;
        int count = 0;
        int64_t length = 2;
        while ( length <= floor( sqrt(2*trg + 0.25 ) - 0.5 ) ){ // NOTE: 수학적으로 수식 계산해 놓기
            int64_t seqSum = GetSeqSum(length);

            if ( (trg - seqSum) % length == 0)
                count++;
            length++;
        }
        cout << count << "\n";
    }
    
    return 0;
}