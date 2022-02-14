/* 6549 히스토그램에서 가장 큰 직사각형
 *
 * smsh0722
 * */
#include <iostream>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n;
    while ( true ){
        cin >> n;
        if ( n == 0 )
            break;

        int64_t max = 0;
        int left_end[n];
        int right_end[n];
        int histo[n];
        for ( int i = 0; i < n; i++ )
            cin >> histo[i];
        /* Build left end */
        left_end[0] = -1;
        for ( int i = 1; i < n; i++ ){
            int trgIdx = i - 1;
            while ( trgIdx > -1 ){
                if ( histo[trgIdx] >= histo[i] )
                    trgIdx = left_end[trgIdx];
                else 
                    break;
            }
            left_end[i] = trgIdx;
        }
        /* Build right end*/
        right_end[n-1] = n;
        for ( int i = n - 2; i >= 0; i-- ){
            int trgIdx = i + 1;
            while ( trgIdx < n ){
                if ( histo[trgIdx] >= histo[i] )
                    trgIdx = right_end[trgIdx];
                else 
                    break;
            }
            right_end[i] = trgIdx;
        }
        /* Answer */
        for ( int i = 0; i < n; i++ ){
            int64_t curr_max = ( right_end[i] - left_end[i] - 1 ) * (int64_t)histo[i];
            max = max < curr_max ? curr_max : max;
        }
        cout << max << "\n";
    }    

    return 0;
}
