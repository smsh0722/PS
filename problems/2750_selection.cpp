/* Selection Sort
*/
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
    for ( int i = 0; i < N; i++ )
        cin >> arr[i];

    /* Sort
            i         
    1 3 5 6 4
        j
    */
    for ( int i = 0; i < N; i++ ){
        int minIdx = i;
        for ( int j = i; j < N; j++ ){
            minIdx = arr[minIdx] > arr[j] ? j : minIdx;
        }
        swap( arr[minIdx], arr[i] );
    }

    // Print
    for ( int i = 0; i < N; i++ )
        cout << arr[i] << "\n";

    return 0;
}