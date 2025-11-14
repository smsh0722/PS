/* NOTE:
Naive한 풀이로부터 하나씩 아이디어를 떠올려보자.

*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;

vector<int> snowballs;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    snowballs.resize(N);
    for ( int ni = 0; ni < N; ni++ )
        cin >> snowballs[ni];

    sort( snowballs.begin(), snowballs.end() );

    int ans = INT32_MAX;
    for ( int i = 0; i < N; i++ ){
        for ( int j = i + 1; j < N; j++ ){
            int snowman1 = snowballs[i] + snowballs[j];
            int snowman2 = 0;

            int l = 0;
            int r = N-1;
            while ( l < r ){
                if ( l != i && l != j && r != i && r!= j ){
                    snowman2 = snowballs[l] + snowballs[r];
                    ans = min( ans, abs(snowman1-snowman2));
                }
                if ( snowman1 < snowman2 ){
                    r--;
                }
                else { // snowman1 >= snowman2
                    l++;
                }
            }
        }
    }
    
    cout << ans;
    return 0;
}