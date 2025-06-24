#include <iostream>
#include <vector>

using namespace std;

void IterSwap( vector<int>& arr, int trg, int cur );

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    int N, S;
    vector<int>arr(50);


    cin >> N;
    for ( int i = 0; i < N; i++ )
        cin >> arr[i];
    cin >> S;

    for ( int i = 0; i < N && S > 0; i++ ){
        int maxNum = arr[i];
        int maxIdx = i;
        for ( int j = i+1; j < N && (j-i) <= S ; j++){
            if ( maxNum < arr[j] ){
                maxNum = arr[j];
                maxIdx = j;
            }
        }
        if ( maxIdx != i ){
            IterSwap( arr, i, maxIdx );
            S -= ( maxIdx - i);
        }
    }

    for ( int i = 0; i < N; i++ )
        cout << arr[i] << " ";
}

void IterSwap( vector<int>& arr, int trg, int cur )
{
    // swap arr[l] & arr[r]
    int l = cur - 1;
    int r = cur;
    while ( l >= trg && l >= 0){
        int temp = arr[r];
        arr[r] = arr[l];
        arr[l] = temp;
        l--; r--;
    }
}