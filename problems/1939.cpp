#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Edge{
    int u, v, c;
};

int N;
int M;

int dst1, dst2;

vector<Edge> edges;
vector<int> parents;
vector<int> limits;

bool CompareEdgeDesc( const Edge& a, const Edge& b )
{
    return a.c > b.c;
};

int GetParentRecursive( int a )
{
    return parents[a] == a ? a : ( parents[a] = GetParentRecursive(parents[a]) );
}
void Union( int u, int v, int c )
{
    int pu = GetParentRecursive(u);
    int pv = GetParentRecursive(v);

    int minLimit = min( c, min(limits[pu], limits[pv] ) );
    parents[pv] = pu;
    limits[pu] = minLimit;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;

    edges.resize(M);
    for ( int mi = 0; mi < M; mi++ ){
        int u, v, c;
        cin >> u >> v >> c;
        edges[mi] = {u,v,c};
    }
    sort( edges.begin(), edges.end(), CompareEdgeDesc );

    cin >> dst1 >> dst2;

    int ans = -1;
    // Solve
    parents.resize(N+1);
    for ( int i = 0; i <= N; i++ )
        parents[i] = i;
    limits.resize(N+1, INT32_MAX);
    for ( auto edge : edges){
        int pu = GetParentRecursive(edge.u);
        int pv = GetParentRecursive(edge.v);
        if ( pu == pv )
            continue;
        
        Union( edge.u, edge.v, edge.c );

        int pDst1 = GetParentRecursive(dst1);
        int pDst2 = GetParentRecursive(dst2);
        if ( pDst1 == pDst2 ){
            ans = limits[pDst1];
            break;
        }
    }

    cout << ans;
    
    return 0;
}