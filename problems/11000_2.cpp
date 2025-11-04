/* SOL2)
스위핑으로 겹치는 수업 체크하면 된다.
*/
#include <iostream>
#include <queue>
using namespace std;

struct Time{
    int s, e;
};
struct TimeAscByS{
    bool operator()( const Time& a, const Time& b )
    {
        if ( a.s == b.s )
            return a.e > b.e;
        return a.s > b.s;
    }
};
struct TimeAscByE{
    bool operator()( const Time& a, const Time& b )
    {
        if ( a.e == b.e )
            return a.s > b.s;
        return a.e > b.e;
    }
};

int N;

priority_queue<Time, vector<Time>, TimeAscByS> nextClasses;
priority_queue<Time, vector<Time>, TimeAscByE> activeClasses;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int i = 0; i < N; i++ ){
        int s, e;
        cin >> s >> e;
        nextClasses.push({s,e});
    }

    int ans = 0;
    while ( nextClasses.empty() == false ){
        Time cur = nextClasses.top();
        nextClasses.pop();

        activeClasses.push(cur);
        while( activeClasses.empty() == false ){
            Time activeClass = activeClasses.top();
            if ( activeClass.e <= cur.s ){
                activeClasses.pop();
            }
            else 
                break;
        }

        ans = max( ans, int(activeClasses.size()) );
    }

    cout << ans;

    return 0;
}