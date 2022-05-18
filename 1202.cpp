/* smsh0722
 * 1202
 * 보석 도둑
 * */
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

/* Gem
 * int M : weight
 * int V : value
 * */
struct Gem{
    int M;
    int V;
};

bool mComp( Gem a, Gem b );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    /* # of gem */
    int N;
    /* # of bags */
    int K;
    
    cin >> N >> K;

    vector<Gem> gems;
    {
        int M, V;
        for ( int i = 0; i < N; i++ ){
            cin >> M >> V;
            gems.push_back( Gem{M, V} );
        }

        sort( gems.begin(), gems.end(), mComp );
    }
    priority_queue<int> bags;
    {
        for ( int i = 0; i < K; i++ ){
            int c;
            cin >> c;
            bags.push( -c );
        }
    }

    int64_t sum = 0;
    {
        int gemIdx = 0;
        priority_queue<int> pq;

        while ( bags.empty() == false ){
            int c = -bags.top();
            bags.pop();

            while ( gemIdx < N ){
                if ( gems[gemIdx].M <= c ){
                    pq.push( gems[gemIdx].V );
                    gemIdx++;
                }
                else 
                    break;
            }

            if ( pq.empty() == false ){
                sum += int64_t(pq.top());
                pq.pop();
            }
        }
    }

    // Print rst
    cout << sum;

    return 0;
}

bool mComp( Gem a, Gem b )
{
    return a.M < b.M;
}