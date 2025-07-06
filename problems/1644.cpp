#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 4000000;
const int SQAURE_ROOT_MAX_N = 2000;

int N;

vector<bool> bIsPrime(MAX_N +1, true );
vector<int> primeVec;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    for ( int i = 2; i <= SQAURE_ROOT_MAX_N; i++ ){
        if ( bIsPrime[i] == false )
            continue;
        for ( int j = 2; i *j <= MAX_N; j++ ){
            bIsPrime[i*j]= false;
        }
    }
    for ( int i = 2; i <= MAX_N; i++ ){
        if ( bIsPrime[i] == true )
            primeVec.push_back(i);
    }

    int count = 0;
    {
        int l = 0, r = -1;
        int sum = 0;
        const int size = primeVec.size();
        while ( l< size && r < size ){
            if( sum < N ){
                r++;
                sum += primeVec[r];
            }
            else if ( sum > N ){
                sum -= primeVec[l];
                l++;
            }
            else { //sum == N
                count++;
                r++;
                sum += primeVec[r];
            }
        }
    }

    cout << count;
    
    return 0;
}