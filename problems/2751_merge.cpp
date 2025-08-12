// Merge Sort
#include <iostream>
#include <vector>
using namespace std;

int N;

vector<int> arr;

void MergeSort( int l, int r )
{
    if ( l == r )
        return;
    
    // Divide
    int mid = (r-l)/2 + l;
    MergeSort(l, mid);
    MergeSort(mid+1, r);

    // Merge
    vector<int> left(mid-l+1);
    vector<int> right(r-mid);
    for ( int i = l; i <= mid; i++ )
        left[i-l] = arr[i];
    for ( int i = mid+1; i <= r; i++ )
        right[i-(mid+1)] = arr[i];


    size_t li = 0;
    size_t ri = 0;
    for ( int i = l; i <= r; i++ ){
        if ( li >= left.size() ){
            arr[i] = right[ri++];
        }
        else if ( ri >= right.size() ){
            arr[i] = left[li++];
        }
        else {
            if ( left[li] < right[ri] )
                arr[i] = left[li++];
            else 
                arr[i] = right[ri++];
        }
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    arr.resize(N);
    for ( int i = 0; i < N; i++ )
        cin >> arr[i];

    MergeSort(0, N-1);

    for ( int i = 0; i < N; i++ )
        cout << arr[i] << "\n";
    
    return 0;
}