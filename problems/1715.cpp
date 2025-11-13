#include <iostream>
#include <queue>
using namespace std;

struct PQCompareAsc{
    bool operator()( const int64_t& a, const int64_t& b ) 
    {
        return a > b;
    }
};

int N;
priority_queue<int64_t, vector<int64_t>, PQCompareAsc> pq;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int ni = 0; ni < N; ni++ ){
        int64_t val;
        cin >> val;
        pq.push(val);
    }

    int64_t ans = 0;
    while (pq.size() > 1 ){
        int64_t a, b;
        a = pq.top(); 
        pq.pop();
        b = pq.top();
        pq.pop();

        int64_t sum = a + b;
        ans += sum;
        pq.push(sum);
    }

    cout << ans;

    return 0;
}