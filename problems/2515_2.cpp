/* NOTE: 성공
축이 올바른 가 생각하는게 중요했다.
1번 풀이는 축에 예외가 존재하기 때문에 불가능하다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

struct Paint {
    int h, c;
};

// # of paints
int N;
// size of Min
int S;

vector<Paint> paints;
vector<int> heights;
vector<int> dpTable;

bool ComaprePaintAscByH( const Paint& a, const Paint& b )
{
    if ( a.h == b.h )
        return a.c < b.c;
    return a.h < b.h;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Input
    cin >> N >> S;
        // Get Paints datas
    paints.resize(N);
    heights.resize(N);
    for ( int pi = 0; pi < N; pi++ ){
        cin >> paints[pi].h >> paints[pi].c;
        heights[pi] = paints[pi].h;
    }
    sort( paints.begin(), paints.end(), ComaprePaintAscByH);
    sort( heights.begin(), heights.end() );

    // Build DP Table
    dpTable.resize(N, -1);
    dpTable[N-1] = heights[N-1] >= S ? paints[N-1].c : 0;

    priority_queue<int> pq;
    if ( paints[N-1].h >= S )
        pq.push(dpTable[N-1]);
    for ( int i = N-2; i >=0; i-- ){
        int lb = lower_bound( heights.begin(), heights.end(), heights[i] + S ) - heights.begin();
        int includeCost = heights[i] >= S ? paints[i].c : 0;
        if ( lb < N ) includeCost += dpTable[lb];
        pq.push(includeCost);
        dpTable[i] = pq.top();
    }

    cout << dpTable[0];

    return 0;
}