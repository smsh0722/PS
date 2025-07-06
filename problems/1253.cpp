#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;


int N;

vector<int> arr;

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    for ( int i = 0; i < N; i++ ){
        int a;
        cin >> a;
        arr.push_back(a);
    }

    sort(arr.begin(), arr.end() );

    int count = 0;
    {
        for ( int i = 0; i < N; i++ ){
            int l = 0, r = arr.size()-1;
            while ( l < r ){
                if ( l == i ){
                    l++;
                    continue;
                }
                if ( r == i) {
                    r--;
                    continue;
                }

                int sum = arr[l] + arr[r];
                if ( sum == arr[i] ){
                    count++;
                    break;
                }
                else if( sum > arr[i] ){
                    r--;
                }
                else { // sum < arr[i]
                    l++;
                }
            }
        }
    }
    cout << count;
    return 0;
}