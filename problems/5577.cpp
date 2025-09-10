#include <iostream>
#include <vector>
using namespace std;

vector<int> arr;
int N;

inline int GetResultLeft( int startIdx )
{
    int l = startIdx;
    int r = startIdx+1;
    while ( l >= 0 && r < N ){
        int color = arr[l];
        int lCount = 1;
        int rCount = 0;
        for ( int i = l-1; i >= 0; i-- ){
            if ( color == arr[i] )
                lCount++;
            else 
                break;
        }
        for ( int i = r; i < N; i++ ){
            if ( color == arr[i] )
                rCount++;
            else 
                break;
        }

        if ( (lCount+rCount) >= 4 ){
            l = l - lCount;
            r = r + rCount;
        }
        else {
            break;
        }
    }

    return (l+(N-r)+1);
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    arr.resize(N);
    for ( int i = 0; i < N; i++ ){
        cin >> arr[i];
        arr[i] -= 1;
    }

    int ans = 10001;
    for ( int i = 0; i < N; i++ ){
        int original = arr[i];

        // Case1
        arr[i] = (original + 1)%3;
        ans = min( ans, GetResultLeft(i+1) );
        // Case2
        arr[i] = (original + 2)%3;
        ans = min( ans, GetResultLeft(i+1) );
        // Rollback
        arr[i] = original;
    }   

    cout << ans;

    return 0;
}