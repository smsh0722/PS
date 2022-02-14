#include <iostream>
using namespace std;

void minHeapify( int size, int* arr, int target );
void swapFunc( int* arr, int a, int b );

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int caseN; cin >> caseN;
    
    int* arr = new int[caseN];
    int idx = -1;
    int temp;
    for ( int i = 0; i < caseN; i++ ){
        cin >> temp;
        
        if ( temp == 0 ){
            if ( idx == -1 ) cout << 0 << "\n";
            else { // idx >= 0
                cout << arr[0] << "\n";
                swapFunc( arr, 0, idx );
                idx--;
                for( int i = ( idx - 1 ) / 2; i >= 0; i-- ) minHeapify( idx, arr, i );
            }
        }
        else {
            idx++;
            arr[idx] = temp;
            for ( int i = ( idx - 1 ) / 2; i >= 0; i-- ) minHeapify( idx, arr, i );
        }
    }
}

void minHeapify( int size, int* arr, int target ){
    int p = target;
    int cL = p * 2 + 1;
    int cR = p * 2 + 2;

    if ( cL <= size && arr[p] > arr[cL] ){
        target = cL;
    }
    if ( cR <= size && arr[p] > arr[cR] ){
        target = cR;
    }

    if ( p != target ){
        swapFunc( arr, p, target );
        minHeapify( size, arr, target );
    }
}

void swapFunc( int* arr, int a, int b ){
    int temp;
    temp = arr[a];
    arr[a] = arr[b];
    arr[b] = temp;
}