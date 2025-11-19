#include <iostream>
#include <vector>
#include <map>
using namespace std;

const int MAX_PRICE = 500000;

// # of candies
int N;
// candies<price, # of cases>
map<int, int> candies;

int64_t* cases = new int64_t[MAX_PRICE+1](); // NOTE: new 0 초기화

vector<bool> primes( MAX_PRICE+1, true);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    cases[0] = 1;
    for ( int ni = 0; ni < N; ni++ ){
        int c;
        cin >> c;

        if ( c== 0 ){
            cases[0]++;
            continue;
        }
        if ( candies.find(c) == candies.end() )
            candies[c] = 1;
        else 
            candies[c]++;
    }

    for ( auto candy: candies ){
        int64_t* tmp = new int64_t[MAX_PRICE+1]();
        tmp[0] = cases[0];

        for ( int p = 0; p <= MAX_PRICE; p++ ){
            for ( int num = 0; num <= candy.second; num++ ){
                int newPrice = p + num*candy.first;
                if ( newPrice > MAX_PRICE )
                    continue;
                if ( newPrice == 0 )
                    continue;
                tmp[newPrice] += cases[p];
            }
        }

        delete[] cases;
        cases = tmp;
    }

    for ( int i = 2; i*2 <= MAX_PRICE; i++ ){
        if ( primes[i] == false )
            continue;

        int mul = 2;
        while ( i * mul <= MAX_PRICE ){
            primes[i*mul] = false;
            mul++;
        }
    }

    int64_t ans = 0;
    for ( int p = 2; p <= MAX_PRICE; p++ ){
        // cout << p << " : " << cases[p] << endl; // DEBUG
        if ( primes[p] == true ){
            // cout << "Include!\n"; // DEBUG
            ans += cases[p];
        }
    }

    cout << ans;

    return 0;
}