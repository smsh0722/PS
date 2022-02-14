#include <iostream>
#include <set>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false);

    set<int> data;

    int SIZE; cin >> SIZE;
    int* arr = new int[SIZE];

    // Set data
    for ( int i = 0; i < SIZE; i++ ){
        cin >> arr[i];
        data.insert( arr[i] );
    }
    
    int SIZE2 = data.size();
    int* arr2 = new int[SIZE2];
    int idx = 0;
    for ( set<int>::iterator it = data.begin(); it != data.end(); it++ ){
        arr2[idx] = *it;
        idx++;
    }
    
    // Print out
    int lEnd, rEnd;
    for ( int i = 0; i < SIZE; i++ ){
        lEnd = 0; rEnd = SIZE2 - 1;

        while ( lEnd <= rEnd ){
            idx = ( lEnd + rEnd ) / 2;

            if ( arr2[idx] == arr[i] ){
                cout << idx << " ";
                break;
            }
            else if ( arr2[idx] > arr[i] )
                rEnd = idx - 1;
            else    //arr2[idx] < arr[i]
                lEnd = idx + 1;
        }
    }
}