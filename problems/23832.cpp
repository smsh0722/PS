#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int N;

int maxFactor = 1;

vector<bool> primes;

void printFactors( int num, const vector<int>& factors )
{
    cout << "Factors of " << num << endl;
    for ( auto factor: factors )
        cout << factor << " ";
    cout << endl;
}

int CalCasesNum( const vector<int>& factors, int leftInclude, int prevIdx, int minNum, int num )
{
    if ( leftInclude == 0 ){
        return (N/num - minNum/num);
    }

    int rst = 0;
    for ( size_t i = prevIdx +1; i < factors.size(); i++ ){
        int factor = factors[i];
        rst += CalCasesNum( factors, leftInclude-1, i, minNum, num*factor);
    }

    return rst;
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    // Sieve
    maxFactor = sqrt(N)+1;
    primes.resize(maxFactor+1, true);
    for ( int i = 2; i <= maxFactor; i++ ){
        if ( primes[i] == false )
            continue;

        for ( int j = 2; i*j <= maxFactor; j++ ){
            primes[i*j] = false;
        }
    }

    int ans = N-1; // NOTE: 1 은 기본적으로 N-1개와 이미 서로소
    // 각 숫자의 서로소 구하기
    for ( int i = 2; i <= N; i++ ){
        // 인수분해
        int num = i;
        vector<int> factors;
        for ( int p = 2; p <= maxFactor; p++ ){
            bool bFactor = false;
            while ( num % p == 0){
                num /= p;
                bFactor = true;
            }
            if ( bFactor == true)
                factors.push_back(p);
        }
        if ( num != 1 )
            factors.push_back(num);

        // printFactors( i, factors); // DEBUG
        // 여집합 구하기(포함배제)
        int count = N - i;
        int complementCount = 0;
        for ( size_t interSize = 1; interSize <= factors.size(); interSize++){
            if (interSize % 2 == 1 )
                complementCount += CalCasesNum(factors, interSize, -1, i, 1);
            else // inteerSize % 2 == 0
                complementCount -= CalCasesNum(factors, interSize, -1, i, 1);
        }

        ans += count - complementCount;
    }

    // Answer
    cout << ans;

    return 0;
}