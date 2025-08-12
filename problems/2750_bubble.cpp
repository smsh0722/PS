// Bubble Sort
// O(N^2)
// O(NlogN)은 2751번
#include <iostream>
#include <vector>
using namespace std;

int N;
vector<int> arr;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    arr.resize(N);
    for ( int i = 0; i < N; i++ ){
        cin >> arr[i];
    }

    // bubble sort
    for ( int r = N -1; r > 0; r-- ){
        for ( int i = 0; i < r; i++ ){
            if ( arr[i] > arr[i+1] ){
                int tmp = arr[i+1];
                arr[i+1] = arr[i];
                arr[i] = tmp;
            }
        }
    }
    
    // Output
    for ( int i = 0; i < N; i++ )
        cout << arr[i] << " ";

    return 0;
}