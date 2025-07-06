/*
tow pointer
2467.cpp 에선 binary search로 풀었음. 비교해보기
*/
#include <iostream>
#include <vector>

using namespace std;

const int MAX_INT = ~(1<<31);
const int MAX_N = 100000;

int N; 
vector<int> liquids(MAX_N);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int i = 0; i < N; i++ ){
        cin >> liquids[i];
    }

    int minSum = MAX_INT;
    int minL, minR;
    {
        int l = 0, r = N-1;
        while ( l < r ){
            int sum = liquids[r] + liquids[l];
            
            if ( minSum > abs(sum) ){
                minSum = abs(sum);
                minL = l;
                minR = r;
            }

            if ( sum > 0 ){
                r--;
            }
            else {
                l++;
            }
        }
    }

    cout << liquids[minL] << " " << liquids[minR];

    return 0;
}