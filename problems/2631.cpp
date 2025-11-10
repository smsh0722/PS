#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// # of children
int N;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    vector<int> lis = {INT32_MAX};
    for ( int ni = 0; ni < N; ni++ ){
        int c;
        cin >> c;

        if ( lis.back() < c )
            lis.push_back(c);
        else {
            int idx = lower_bound(lis.begin(), lis.end(), c ) - lis.begin();
            lis[idx] = c;
        }
    }

    cout << N - lis.size();

    return 0;
}