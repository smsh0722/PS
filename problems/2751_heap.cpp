// HeapSort
#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N;

int sortCount = 0;
vector<int> arr;

void MaxHeapify( int p )
{
    int limit = N - sortCount;
    while ( p < limit ){
        int trg = p;
        int lc = p*2+1;
        int rc = p*2+2;
        if ( lc < limit && arr[p] < arr[lc] )
            trg = lc;
        if ( rc < limit && arr[trg] < arr[rc] )
            trg = rc;
        if ( trg == p )
            break;
        swap( arr[p], arr[trg] );
        p = trg;
    }
}
void HeapSort()
{
    // build max heap: sift down
    for ( int i = N/2-1; i >= 0; i-- ){
        MaxHeapify(i);
    }

    // Loop
    while ( sortCount < N ){
        // L1: Get max
        swap( arr[0], arr[N-1-sortCount] );
        sortCount++;

        // L2: sift down
        MaxHeapify(0);
    }

}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;
    arr.resize(N);
    for ( int i = 0; i < N; i++ )
        cin >> arr[i];

    HeapSort();

    for ( int i = 0; i < N; i++ )
        cout << arr[i] << "\n";

    return 0;
}

// // Heap Sort
// #include<iostream>
// #include <vector>
// using namespace std;

// const int MAX_INT = ~(1<<31);
// int N;

// // Min Heap
// int hSize = 0;
// vector<int> arr;

// void MinHeapify()
// {
//     int cur = 0;
//     while ( cur < hSize ){
//         int trg = cur;
//         int lc = cur*2+1;
//         int rc = cur*2+2;

//         if ( lc < hSize && arr[cur] > arr[lc] )
//             trg = lc;
//         if ( rc < hSize && arr[trg] > arr[rc] )
//             trg = rc;
        
//         if ( trg == cur )
//             break;
//         swap(arr[cur], arr[trg]);

//         cur = trg;
//     }
// }
// void Push( int x )
// {
//     int ci = hSize;
//     int pi = (ci-1)/2;

//     arr[hSize++] = x;
//     while ( ci > 0 ){
//         if ( arr[pi] <= arr[ci] )
//             break;
//         swap(arr[pi], arr[ci]);
//         ci = pi;
//         pi = (pi-1)/2;
//     }
// }

// int Pop( )
// {
//     if ( hSize == 0 )
//         return MAX_INT;
    
//     int top = arr[0];
//     arr[0] = arr[--hSize];

//     MinHeapify();

//     return top;
// }

// int main( void )
// {
//     ios_base::sync_with_stdio(false); cin.tie(NULL);

//     cin >> N;
//     arr.resize(N, MAX_INT);
    
//     for ( int i = 0; i < N; i++ ){
//         int a;
//         cin >> a;
//         Push(a);
//     }

//     while ( hSize > 0 ){
//         cout << Pop() << "\n";
//     }

//     return 0;
// }