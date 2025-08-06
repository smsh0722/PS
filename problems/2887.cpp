/* NOTE:
MST 관련은 확실.

But, 간선 모두 추가하면 너무 많음.
필요한 간선과 처리 방법에 대한 고민.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct Vec2{
    int a, b;
};
struct Vec3{
    int a, b, c;
};

struct Vec3AscByA{
    bool operator()(const Vec3& v1, const Vec3& v2 )
    {
        return v1.a > v2.a;
    };
};

int N;

vector<Vec2> planetsX; // {pos, planet}
vector<Vec2> planetsY; // {pos, planet}
vector<Vec2> planetsZ; // {pos, planet}
priority_queue<Vec3, vector<Vec3>, Vec3AscByA> pq; // val: {cost, p1, p2}

vector<int> parent;
vector<int> ranks;
int64_t totalCost = 0;

bool PlanetPosAsc( const Vec2& p1, const Vec2& p2 )
{
    return p1.a < p2.a;
};

int FindParentRecursive( int x )
{
    return parent[x] == x ? x : (parent[x] = FindParentRecursive( parent[x]));
}
inline void UnionSet( int a, int b )
{
    int pa = FindParentRecursive( a);
    int pb = FindParentRecursive( b);

    if ( ranks[pa] == ranks[pb] ){
        parent[pb] = pa; // NOTE: parent[b] = pa 가 아닌 parent[pb] = pa. 실수 말자.
        ranks[pa]++;
    }
    else if ( ranks[pa] > ranks[pb] ){
        parent[pb] = pa;
    }
    else { // ranks[pa] < ranks[pb]
        parent[pa] = pb;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Init
    cin >> N;
    planetsX.resize(N);
    planetsY.resize(N);
    planetsZ.resize(N);
    parent.resize(N);
    ranks.resize(N,0);
    for ( int i = 0; i < N; i++ ){
        int x, y, z;
        cin >> x >> y >> z;

        planetsX[i] = {x, i};
        planetsY[i] = {y, i};
        planetsZ[i] = {z, i};
        
        parent[i] = i;
    }

    // Sort
    sort( planetsX.begin(), planetsX.end(), PlanetPosAsc );
    sort( planetsY.begin(), planetsY.end(), PlanetPosAsc );
    sort( planetsZ.begin(), planetsZ.end(), PlanetPosAsc );

    // Prepare Kruskal's algorithm
    for ( int i = 0; i < N-1; i++ ){
        pq.push({planetsX[i+1].a-planetsX[i].a, planetsX[i+1].b, planetsX[i].b});
        pq.push({planetsY[i+1].a-planetsY[i].a, planetsY[i+1].b, planetsY[i].b});
        pq.push({planetsZ[i+1].a-planetsZ[i].a, planetsZ[i+1].b, planetsZ[i].b});
    }

    // Build MST
    int edgeCount = 0;
    while ( pq.empty() == false && edgeCount < N-1){
        Vec3 top = pq.top();
        pq.pop();

        int pa = FindParentRecursive(top.b);
        int pb = FindParentRecursive(top.c);

        if ( pa == pb )
            continue;
        UnionSet( top.b, top.c );
        totalCost += int64_t( top.a );
        edgeCount++;
    }

    cout << totalCost;

    return 0;
}