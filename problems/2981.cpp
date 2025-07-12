#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_INT = ~(1<<31);

int N;
vector<int> diff; // diff[i] = Ai - A0;
vector<int> ans;

int gcdRecursive( int a, int b )
{
    int r = a % b;
    if ( r == 0 )
        return b;
    return gcdRecursive(b, r);
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    diff.resize(N, 0); 
    {
        int a0;
        int cur;
        cin >> a0;
        for( int i = 1; i < N; i++ ){
            cin >> cur;
            diff[i] = abs(cur - a0);
        }
    }
    
    int gcd = diff[1];
    for ( int i = 2; i < N; i++ ){
        gcd = gcdRecursive(gcd, diff[i]);
    }

    // 약수들 출력
    ans.push_back(gcd);
    for ( int i = 2; i * i <= gcd; i++ ){
        if ( gcd % i == 0 ){
            ans.push_back(i);
            
            int q = gcd / i;
            if ( q != i )
                ans.push_back(q);
        }
    }

    sort(ans.begin(), ans.end() );

    for ( size_t i = 0; i < ans.size(); i++ ){
        cout << ans[i] << " ";
    }

    return 0;
}