/* NOTE:
모든 조합을 시도하면 N! 이다.
bruteforce는 불가능

대신 반복되는 부분이 있기 때문에 dp 쓰면된다.
이때, 조합을 표시하기 위해서 bitmask를 사용하면 된다.

또한, 큰 수의 나머지, 나머지 연산과 분배 법칙 등 수학적 구현도 잘 생각해야한다.
*/
#include <iostream>
#include <string>
#include <vector>
using namespace std;

const int MAX_LEN = 751;

// # of elements
int N;
// elements(nums)
vector<string> nums;
// Divisor
int K;
// Total Len of final num
int totalLen = 0;

// memo[mask][remainder] = # 
vector<vector<int64_t>> memo;

/* 
NOTE: 아래 두 나머지 값들은 계속 사용되기 때문에 미리 구하는 것이 좋다.
미리 계산하지 않는 경우 시간 초과가 발생했다.
*/
vector<int> remains;
vector<int> pow10Remains(MAX_LEN,1);

int64_t GCD( int64_t a, int64_t b)
{
    return b == 0 ? a : GCD(b, a % b);
}
inline int GetRemain( const string& numStr )
{
    int lb = 0;
    int rb = 5;
    int remain = 0;
    while ( lb < numStr.length() ){
        string subNumStr = "";
        subNumStr = numStr.substr(lb, rb);

        if ( remain != 0 )
            subNumStr = to_string(remain) + subNumStr;
        int subNum = stoi(subNumStr);
        remain = subNum % K;
        lb += rb;
    }

    return remain;
}
int64_t Solve( int leftLen, int usedBits, int remainder )
{
    if ( leftLen == 0 )
        return remainder == 0 ? 1 : 0;
    if( memo[usedBits][remainder] != -1 )
        return memo[usedBits][remainder];
    
    int64_t rst = 0;
    for ( int i = 0; i < N; i++ ){
        int tryNumMask = 1<<i;
        if ( usedBits&tryNumMask )
            continue;

        int nextLeftLen = leftLen - nums[i].length();
        int remain = (remains[i]*pow10Remains[nextLeftLen])%K;
        rst += Solve( nextLeftLen, usedBits|tryNumMask, (K+remainder-remain)%K );
    }

    return memo[usedBits][remainder] = rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    nums.resize(N);
    for ( int ni = 0; ni < N; ni++ ){
        cin >> nums[ni];
        totalLen += nums[ni].length();
    }
    cin >> K;

    // Preprocess
    remains.resize(N, 0);
    for ( int ni = 0; ni < N; ni++ )
        remains[ni] = GetRemain(nums[ni]);
    for (int i = 1; i < MAX_LEN;i++ ){
        pow10Remains[i] = (pow10Remains[i-1] * 10)%K;
    }

    memo.resize( 1<<N, vector<int64_t>(K, -1) );
    // Print answer
    int64_t allCases = 1;
    for ( int64_t i = 1; i <= N; i++ )
        allCases *= i;
    int64_t ansCases = Solve(totalLen,0,0);
    int64_t gcd = GCD( allCases, ansCases );
    // cout << ansCases << "/" << allCases << " gcd: " << gcd << endl;// DEBUG
    if ( ansCases == 0 )
        cout << ansCases << "/" << 1 << endl;
    else 
        cout << ansCases/gcd << "/" << allCases/gcd << endl;

    return 0;
}