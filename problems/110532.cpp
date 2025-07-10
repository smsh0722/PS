#include <iostream>
#include <vector>
using namespace std;

int N; 
vector<int> arr;
vector<int> bucket;

void SwapForLIS( int val );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    arr.resize(N );
    for ( int i = 0; i < N; i++ )
        cin >> arr[i];

    bucket.push_back(arr[0]);
    for ( int i = 1; i < N; i++ ){
        if ( bucket.back() <= arr[i] ){
            bucket.push_back(arr[i]);
        }
        else {
            SwapForLIS( arr[i] );
        }
    }

    for ( size_t i = 0; i < bucket.size(); i++ ){ // Debug
        cout << bucket[i] << " ";
    } cout << "\n"; 

    cout << N - int( bucket.size() );
}

void SwapForLIS( int val )
{
    int l = 0;
    int r = bucket.size() - 1;
    while ( l < r ){
        int mid = ( r - l ) / 2 + l;

        if (bucket[mid] >= val ){
            r = mid;
        }
        else { // bucek[mid] < val
            l = mid + 1;
        }
    }
    if ( l == r && bucket[l] >= val ){
        bucket[l] = val;
    }
}