#include <iostream>
#include <algorithm>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    
    // Set data
    cin >> N;
    int card[N];
    for ( int i = 0; i < N; i++ )
        cin >> card[i];
    sort( card, card + N );
   
    /*
    for( int i = 0; i < N; i++ )
        cout << card[i] << " ";
    */

    // Find
    int mid, lEnd, rEnd;
    int target;
    int result;

    cin >> M;
    for( int i = 0; i < M; i++ ){
        cin >> target;
        lEnd = 0; rEnd = N - 1;
        result = 0;

        while( rEnd >= lEnd ){
            mid = ( lEnd + rEnd ) / 2;
            if ( card[mid] > target )
                rEnd = mid - 1;
            else // card[mid] <= target
                lEnd = mid + 1;
        }
        result = rEnd;

        lEnd = 0; rEnd = N - 1;
        while ( rEnd >= lEnd ){
            mid = ( lEnd + rEnd ) / 2;
            if ( card[mid] >= target )
                rEnd = mid - 1;
            else // card[mid] < target
                lEnd = mid + 1;
        }
        result = result - lEnd + 1;

        cout << result << " ";
    }
}