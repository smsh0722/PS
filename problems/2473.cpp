#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int64_t MAX_INT64 = ~((int64_t)1<<63);

int N;
vector<int64_t> liquids;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
   
    cin >> N;
    for ( int i = 0; i < N; i++ ){
        int64_t val;
        cin >> val;
        liquids.push_back(val);
    }

    sort(liquids.begin(), liquids.end() );

    int64_t minVal = MAX_INT64;
    int minA = 0, minB = 0, minC = 0;
    for ( int a = 0; a < N - 2; a++ ){ // a = [0,N-3]
        int b = a + 1, c = N - 1; // b = [1,N-2], c= N-1
        while ( b < c ){
            int64_t sum = liquids[a] + liquids[b] + liquids[c];
            if( minVal > abs(sum) ){
                minVal = abs(sum);
                minA = a; minB = b; minC =c;
            }

            if ( sum > 0 ){
                c--;
            }
            else {
                b++;
            }
        }
    }

    cout << liquids[minA] << " "
        << liquids[minB] << " "
        << liquids[minC];

    return 0;
}