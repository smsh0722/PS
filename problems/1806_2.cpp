/*
two pointer
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_INT = ~(1<<31);
const int MAX_N = 100000;

int N, S;
vector<int> prefixSum(MAX_N+1, 0);

int main (void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> S;
    for ( int i = 1; i <= N; i++ ){
        cin >> prefixSum[i];
        prefixSum[i] += prefixSum[i-1];
    }

    int minLength = MAX_INT;
    {
        int l = 0, r = 0;
        while ( l <= N && r <= N ){
            int sum = prefixSum[r] - prefixSum[l];
            if ( sum < S )
                r++;
            else { // sum >= S
                minLength = minLength > r - l ? r - l : minLength;
                l++;
            }
        }
    }

    if ( minLength == MAX_INT )
        cout << 0;
    else 
        cout << minLength;

    return 0;
}