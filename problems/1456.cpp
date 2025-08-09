#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_PRIME_RANGE = 10000000;

int64_t A;
int64_t B;
int64_t answer = 0;

vector<bool> primes(MAX_PRIME_RANGE+1, true);

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> A >> B;
    
    for ( int64_t n = 2; n <= MAX_PRIME_RANGE; n++ ){
        if ( primes[n] == false )
            continue;

        int64_t almostPrime = n;
        int64_t ceilMax = B / n;
        while ( almostPrime <= ceilMax ){
            almostPrime *= n;
            answer = A <= almostPrime ? answer + 1: answer;
        }

        int64_t m = 2;
        int64_t newNum = n*m;
        while ( newNum <= MAX_PRIME_RANGE ){
            primes[newNum] = false;

            m++;
            newNum = n*m;
        }
    }

    cout << answer;

    return 0;
}