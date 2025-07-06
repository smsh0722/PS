/*
binary search
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_INT = ~(1<<31);
const int MAX_N = 100000;

int N, S; // N: size of array, S: target sum
vector<int> prefixSum(MAX_N+1, 0); // idx: [0, N], arr[0]: padding

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> S;
    {
        int val;
        for ( int i = 1; i <= N; i++ ){
            cin >> val;
            prefixSum[i] = prefixSum[i-1] + val;
        }
    }

    int minLength = MAX_INT;
    for ( int l = 0; l <= N; l++ ){
        int r = N;
        int prevR = N;
        while ( r > l ){
            if ( prefixSum[r] - prefixSum[l] >= S ){
                if ( minLength > (r-l) )
                    minLength = r - l;
                prevR = r;
                r = (r-l) / 2 + l;
            }
            else{
                int newR = (prevR - r )/ 2 + r;
                if ( newR == r )
                    break;
                r = newR;
            }
        }
    }

    if( minLength == MAX_INT )
        cout << 0;
    else 
        cout << minLength;

    return 0;
}