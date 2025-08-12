/* Insertion Sort
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
    for ( int i = 1; i < N; i++ ){
        for ( int j = i; j >0; j-- ){
            if ( arr[j-1] > arr[j] )
                swap(arr[j-1], arr[j]);
            else 
                break;
        }
    }

    // Print
    for ( int i = 0; i < N; i++ )
        cout << arr[i] << "\n";

    return 0;
}