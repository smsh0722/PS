#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 1000000;
const int MAX_PRIME = 1000;
const int DIVISOR = 987654321;

vector<int> pows(MAX_N+1, 0);
vector<bool> primes(MAX_PRIME+1, true);

int N;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    // Primes 구하기
    for ( int i = 2; i <= MAX_PRIME; i++ ){
        if ( primes[i] == true ){
            for ( int j = 2; i * j <= MAX_PRIME; j++ ){
                primes[i*j] = false;
            }
        }
    }

    // 약수 구하기
    for ( int i = 2; i <= N; i++ ){
        int num = i;
        for ( int j = 2; j*j <= num; j++ ){
            if ( primes[j] == false )
                continue;

            int count = 0;
            while ( num % j == 0 ){
                num /= j;
                count++;
            }
            pows[j] = max(pows[j], count );
        }
        pows[num] = max(pows[num], 1);
    }

    // 정답 구하기
    int64_t ans = 1;
    for ( int i = 2; i <= MAX_N; i++ ){
        int count = pows[i];

        while ( count > 0 ){
            ans *= int64_t(i);
            ans %= DIVISOR;
            count--;
        }
    }

    cout << ans;

    return 0;
}