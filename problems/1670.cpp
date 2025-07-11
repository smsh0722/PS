#include <iostream>
#include <vector>
using namespace std;

const int MAX_N = 10000;
const int64_t DIVISOR = 987654321;

int N;
vector<int64_t> table(5000+1, 0);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    table[0] = 1;
    table[1] = 1;
    for ( int trg = 2; trg <= MAX_N/2; trg++ ){
        int64_t sum = 0;
        for ( int i = 0; i < trg; i++ ){
            sum += table[i] * table[trg-1-i];
            sum %= DIVISOR;
        }   
        table[trg] = sum;
    }
    cout << table[N/2];

    return 0;
}
