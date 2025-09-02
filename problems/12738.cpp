#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;

vector<int> seq;
vector<int> lis;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    
    seq.resize(N);

    for ( int i = 0; i < N; i++ ){
        cin >> seq[i];
    }

    size_t lisSize = 1;
    lis.push_back(seq[0]);
    for ( int i = 1; i < N; i++ ){
        if ( lis[lisSize-1] < seq[i] ){
            lis.push_back(seq[i]);
            lisSize++;
        }
        else {
            int idx = lower_bound(lis.begin(), lis.end(), seq[i] ) - lis.begin();
            lis[idx] = seq[i];
        }
    }

    cout << lisSize;
    
    return 0;
}