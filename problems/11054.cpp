#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;

vector<int> A;

vector<int> lenOfRevLIS;
vector<int> lenOfForLIS;

inline int GetLen( int a, vector<int>& lis )
{
    if ( lis.back() < a ){
        lis.push_back( a );
        return lis.size();
    }
    else {
        int idx = lower_bound( lis.begin(), lis.end(), a ) - lis.begin();
        lis[idx] = a;
        return (idx + 1);
    }
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    A.resize(N);
    for ( int ni = 0; ni < N; ni++ )
        cin >> A[ni];

    lenOfForLIS.resize(N, 1);
    vector<int> forLIS; 
    forLIS.push_back(A[0]);
    for ( int ni = 1; ni < N; ni++ ){
        lenOfForLIS[ni] = GetLen( A[ni], forLIS );
    }

    lenOfRevLIS.resize(N, 1);
    vector<int> revLIS;
    revLIS.push_back(A[N-1]);
    for ( int ni = N - 2; ni >= 0; ni-- ){
        lenOfRevLIS[ni] = GetLen( A[ni], revLIS );
    }

    int ans = 0;
    for ( int ni = 0; ni < N; ni++ ){
        int sum  = lenOfRevLIS[ni] + lenOfForLIS[ni] - 1;
        ans = max( ans, sum );
    }

    cout << ans;

    return 0;
}