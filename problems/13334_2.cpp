#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

const int MAX_POS = 100000000;

struct Position{
    int l, r;
};
struct OrderRDesc{
    bool operator() ( const Position& a, const Position& b )
    {
        if ( a.r == b.r )
            return a.l < b.l;
        return a.r < b.r;
    };
};

int n;
int d;

vector<Position> hoPairs;
priority_queue<Position, vector<Position>, OrderRDesc> pq;

bool OrderPositionLDesc( const Position& a, const Position& b )
{
    if ( a.l == b.l )
        return a.r > b.r;
    return a.l > b.l;
}

int main (void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> n;
    hoPairs.resize(n, {0,0});
    for ( int i = 0; i < n; i++ ){
        int l, r;
        cin >> l >> r;
        if ( l > r )
            swap(l , r );
        hoPairs[i] = {l,r};
    }
    cin >> d;

    sort( hoPairs.begin(), hoPairs.end(), OrderPositionLDesc);

    int ans = 0;
    for ( int i = 0; i < n; i++ ){
        Position p = hoPairs[i];
        pq.push(p);

        int e = (int)min( int64_t(MAX_POS), int64_t(p.l) + d);

        printf( "p(%d, %d)\n", p.l, p.r ); // Debug
        while ( pq.empty() == false ){
            Position t = pq.top();
            if ( t.r <= e )
                break;
            else
                pq.pop();
        }

        int tmp = pq.size();
        ans = ans < tmp ? tmp : ans;
    }

    cout << ans;

    return 0;
}