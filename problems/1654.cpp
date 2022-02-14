#include <iostream>
using namespace std;

int main( void )
{
    int K, N;
    cin >> K >> N;

    // Set data   
    unsigned int* lanLen = new unsigned int[K];
    unsigned int max = 0;
    for ( int i = 0; i < K; i++ ){
        cin >> lanLen[i];
        max = max < lanLen[i] ? lanLen[i] : max;
    }

    // Find max length
    unsigned int lEnd, rEnd, mid;
    lEnd = 1; rEnd = max;
    int num;

    while ( lEnd <= rEnd ){
        mid = ( lEnd + rEnd ) / 2;
        
        num = 0;
        for ( int i = 0; i < K; i++ ) num += lanLen[i] / mid;

        if ( num >= N )
            lEnd = mid + 1;
        else // num < N; 
            rEnd = mid - 1;
    }

    cout << rEnd << "\n";
}