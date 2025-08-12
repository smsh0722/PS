#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const int MAX_COMB_N = 18;

// prob of A
int A;
// prob of B
int B;

vector<int> primes = { 2, 3, 5, 7, 11, 13, 17 };
vector<vector<int>> combinations(MAX_COMB_N+1, vector<int>(MAX_COMB_N+1, 1));

void CalculateCombinations()
{
    /*          1
            1       1
        1       2       1
    1       3       3       1
    */

    for ( int n = 2; n <= MAX_COMB_N; n++ ){
        for ( int r = 1; r < n; r++ ){
            combinations[n][r] = combinations[n-1][r-1] + combinations[n-1][r];
        }
    }
}
double GetPrimeWinProb( int a )
{
    double rst = 0;
    double p = double(a)/double(100);
    int n = MAX_COMB_N;
    for ( size_t i = 0; i < primes.size(); i++ ){
        int r = primes[i];
        rst += double(combinations[n][r])*pow(p,r)*pow(1-p, n-r);
    }

    return rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    CalculateCombinations();

    cin >> A;
    cin >> B;

    double ansA = GetPrimeWinProb(A);
    double ansB = GetPrimeWinProb(B); 

    double ans = ansA + ansB - ansA*ansB;
    printf("%.10f\n", ans);

    return 0;
}