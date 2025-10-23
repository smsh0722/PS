/* NOTE:
처음에는 소 정렬을 하나의 집합으로 처리하였다.
그러나, 두 queue를 두개 사용해야한다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct CowTime{
    int a, b;
};

// # of chicken
int C;
// # of cows
int N;

priority_queue<int> chickens;

struct CompareCowByBDesc{
    bool operator()(const CowTime& x, const CowTime& y )
    {
        return x.b < y.b;
    }
};
struct CompareCowByADesc{
    bool operator()( const CowTime& x, const CowTime& y )
    {
        return x.a < y.a;
    }
};



int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> C >> N;
    for ( int ci = 0; ci < C; ci++ ){
        int t;
        cin >> t;
        chickens.push(t);
    }

    priority_queue<CowTime, vector<CowTime>, CompareCowByBDesc> cowsByB;
    for ( int ni = 0; ni < N; ni++ ){
        int a, b;
        cin >> a >> b;
        cowsByB.push({a,b});
    }

    int ans = 0;
    priority_queue<CowTime, vector<CowTime>, CompareCowByADesc> cowsByA;
    while ( chickens.empty() == false ){
        int chicken = chickens.top();
        chickens.pop();

        while ( cowsByB.empty() == false ){
            CowTime cow = cowsByB.top();

            if ( cow.b < chicken ){
                break;
            }
            // chicken <= cow.b
            cowsByA.push(cow);
            cowsByB.pop();
        }

        while ( cowsByA.empty() == false ){
            CowTime cow = cowsByA.top();
            cowsByA.pop();
            
            if ( cow.a <= chicken ){
                ans++;
                break;
            }
        }
    }

    cout << ans;

    return 0;
}