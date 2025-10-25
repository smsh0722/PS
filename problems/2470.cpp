#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> items;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    items.resize(N);
    for ( int i = 0; i < N; i++ )
        cin >> items[i];
    
    sort( items.begin(), items.end() );

    int minSum = INT32_MAX;
    int minA = -1;
    int minB =-1;
    int l = 0; 
    int r = N-1;
    while ( l < r ){
        int a = items[l];
        int b = items[r];
        int sum = a + b;

        if ( abs(minSum) > abs(sum) ){
            minSum = sum;
            minA = a;
            minB = b;
        }

        if ( sum >= 0 ){
            r--;
        }
        else {
            l++;
        }
    }

    cout << minA << " " << minB;

    return 0;
}