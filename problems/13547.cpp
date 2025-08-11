/*
1) offline query
2) mo's algorithm
두 가지에 대한 이해가 있어야 한다.
Reference: https://www.geeksforgeeks.org/dsa/mos-algorithm-query-square-root-decomposition-set-1-introduction/
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

struct Query{
    int i;
    int l;
    int r;
};

const int MAX_NUM = 1000000;

// size of array
int N;
// size of queries
int M;
// size of block
int blockSize;

vector<int> sum(MAX_NUM+1, 0);
vector<int> seq;
vector<Query> queries;
vector<int> ans;

bool QueryComapre( const Query& a, const Query& b )
{
    int aBlock = a.l/blockSize;
    int bBlock = b.l/blockSize;
    if ( aBlock == bBlock ){
        if ( aBlock&1 )
            return a.r > b.r;
        else 
            return a.r < b.r;
    }

    return aBlock < bBlock;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;
    seq.resize(N+1, 0);
    blockSize = ceil(sqrt(N));
    for( int i = 1; i <= N; i++ ){
        cin >> seq[i];
    }

    cin >> M;
    queries.resize(M);
    ans.resize(M);
    for ( int i = 0; i < M; i++ ){
        cin >> queries[i].l >> queries[i].r;
        queries[i].i = i;
    }
    sort( queries.begin(), queries.end(), QueryComapre );

    int count = 0;
    int curL = 0;
    int curR = 0;
    for ( int i = 0; i < M; i++ ){
        Query q = queries[i];
        
        while (curL < q.l ){
            int trg = seq[curL++];
            sum[trg]--;
            if ( sum[trg] == 0 )
                count--;
        }
        while ( curL > q.l ){
            int trg = seq[--curL];
            sum[trg]++;
            if ( sum[trg] == 1 )
                count++;
        }
        while ( curR < q.r ){
            int trg = seq[++curR];
            sum[trg]++;
            if ( sum[trg] == 1 )
                count++;
        }
        while ( curR > q.r ){
            int trg = seq[curR--];
            sum[trg]--;
            if ( sum[trg] == 0 )
                count--;
        }
        ans[q.i] = count;
    }

    for ( int i = 0; i < M; i++ )
        cout << ans[i] << "\n";

    return 0;
}