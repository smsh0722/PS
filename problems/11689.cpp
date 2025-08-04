#include <iostream>
#include <vector>
using namespace std;

vector<int64_t> divisors;
int64_t n;
int64_t sum = 0;

void CalRecursive( int r, size_t i, int count, int64_t divisor )
{
    if ( r == count ){ // left count == 0
        if ( r % 2 == 1 ){
            sum += (n/divisor);
        }
        else {
            sum -= (n/divisor);
        }

        return;
    }

    int leftCount = r - count;
    for ( ; i <= divisors.size() - leftCount; i++ ){
        CalRecursive(r, i+1, count+1, divisor*divisors[i]);
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n;

    // Get Divisors
    int64_t tmp = n;
    for ( int64_t d = 2; d * d <= n; d++ ){
        if ( tmp % d == 0 )
            divisors.push_back(d);
        while ( tmp % d == 0 ){
            tmp /= d;
        }
    }
    if ( tmp != 1 )
        divisors.push_back(tmp);
    
    for ( size_t i = 0; i < divisors.size(); i++ ) // Debug
        cout << divisors[i] << " ";

    // Calculate # of Case
    for ( size_t r = 1; r <= divisors.size(); r++ ){
        CalRecursive(r, 0, 0, 1);
    } 

    cout << (n - sum);

    return 0;
}