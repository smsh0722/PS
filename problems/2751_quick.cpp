#include <iostream>
#include <vector>
#include <cstdlib> // rand, srand
#include <ctime>    // time
using namespace std;

int N;
vector<int> arr;

void QuickSortRecursive( int l, int r )
{
    if ( l < r ){
        int pivotIdx = rand()%(r-l+1)+l;
        swap(arr[r], arr[pivotIdx]);
        pivotIdx = r;

        // Partioning: [, lower_bound), [lower_bound, ];
        int lower_bound = l;
        for ( int i = l; i < pivotIdx; i++ ){
            if ( arr[i] < arr[pivotIdx] ){
                swap( arr[lower_bound++], arr[i] );
            }
        }
        
        // Set pivot to middle
        swap(arr[lower_bound], arr[pivotIdx]);
        pivotIdx = lower_bound;

        // Do QuickSort Recursively
        QuickSortRecursive(l, pivotIdx-1);
        QuickSortRecursive(pivotIdx+1, r);
    }
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    arr.resize(N);
    for ( int i = 0; i < N; i++ )
        cin >> arr[i];

    srand(time(NULL));
    QuickSortRecursive(0, N-1);

    for ( int i = 0; i < N; i++ )
        cout << arr[i] << "\n";

    return 0;
}