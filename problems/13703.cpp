#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 63;
const int MAX_K = 63;
int n; // time
int k; // pos

vector<vector<uint64_t>> dpMemo(MAX_N+1, vector<uint64_t>(MAX_K*2+1,0)); // [time][pos]

uint64_t SolveRecursive( int pos, int leftTime )
{
    if ( pos == 0 )
        return 0;
    if ( leftTime == 0 )
        return 1;
    if ( dpMemo[leftTime][pos] != 0 )
        return dpMemo[leftTime][pos];

    uint64_t rst = 0;

    rst += SolveRecursive(pos-1, leftTime-1);
    rst += SolveRecursive(pos+1, leftTime-1);

    return ( dpMemo[leftTime][pos] = rst);
}

int main(void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> k >> n;

    cout << SolveRecursive(k, n);

    return 0;
}