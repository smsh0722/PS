#include <iostream>
#include <algorithm>
#include <vector>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false);

    int N, M;
    cin >> N; cin >> M;

    // Set data
    string* data = new string[N];
    for ( int i = 0; i < N; i++ ) cin >> data[i];
    sort( data, data + N );

    // Search
    int lEnd, rEnd, mid;
    int count = 0;
    vector<string> result;

    string target;
    for ( int i = 0; i < M; i++ ){
        cin >> target;
        lEnd = 0; rEnd = N - 1;

        while ( lEnd <= rEnd ){
            mid = ( lEnd + rEnd ) / 2;

            if ( data[mid] == target ){
                count++;
                result.push_back( target );
                break;
            }
            else if ( data[mid] > target )  rEnd = mid - 1;
            else   /* data[mid] < target */ lEnd = mid + 1;
        }
    }
    
    sort( result.begin(), result.end() );

    cout << count << "\n";
    for ( auto it = result.begin(); it != result.end(); it++ )
        cout << *it << "\n";
}