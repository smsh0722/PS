#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// Record pool pos: [s, e)
struct Pool{
    int s;
    int e;
};

// Num of pool
int N;
// Length of plank
int L;

vector<Pool> pools;

bool PoolsCompare( const Pool& pa, const Pool& pb )
{
    return pa.s < pb.s;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> L;
    pools.resize(N);
    for ( int i = 0; i < N; i++ ){
        cin >> pools[i].s >> pools[i].e;
    }
    sort( pools.begin(), pools.end(), PoolsCompare );

    int count = 0;
    int lastFixedBound = 0;
    for ( int pi = 0; pi < N; pi++ ){
        Pool p = pools[pi];
        
        if ( p.e <= lastFixedBound ) // Already fixed
            continue;
        
        // Fix road
        if ( lastFixedBound <= p.s ){ // ex) ffp)pp
            count++;
            lastFixedBound = p.s+L; //ex) 1 + 3 >> 4
            // printf("New LFB: %d\n", lastFixedBound);//Debug
        }
        while ( lastFixedBound < p.e ){
            count++;
            lastFixedBound += L;
            // printf("New LFB: %d\n", lastFixedBound);//Debug
        }
    }

    cout << count;

    return 0;
}