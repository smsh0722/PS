/* Sol) Disjoint_set
한번에 떠올리지 못한 풀이법이지만 이것도 좋은 방법이다.
disjoint set 활용에 익숙해지자.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_WIDTH = 1000;

struct Edge{
    int u, v, width;
};

// # of Vertices
int p;
// # of Edges
int w;

// Capital of Baekjoon
int c;
// Capital of Cube
int v;

vector<Edge> edges;

vector<int> parents;
vector<int> widths;

bool CompareEdge( const Edge& a, const Edge& b )
{
    return a.width > b.width;
}

int GetParentRecursive( int a )
{
    return parents[a] == a ? a : ( parents[a] = GetParentRecursive(parents[a]));
}
void Union( const Edge& edge )
{
    int pu = GetParentRecursive(edge.u);
    int pv = GetParentRecursive(edge.v);
    
    parents[pv] = pu;
    widths[pu] = min( edge.width, min(widths[pu], widths[pv]));
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> p >> w;
    cin >> c >> v;
    edges.resize(w);
    for ( int wi = 0; wi < w; wi++ ){
        int l, m, n;
        cin >> l >> m >> n;
        edges[wi] = {l, m, n};
    }
    sort(edges.begin(), edges.end(), CompareEdge);

    int ans = -1;

    parents.resize(p);
    widths.resize(p, MAX_WIDTH);
    for ( int i = 0; i < p; i++ ){
        parents[i] = i;
    }
    for ( auto edge : edges){
        int pu = GetParentRecursive(edge.u);
        int pv = GetParentRecursive(edge.v);

        if ( pu != pv ){
            Union( edge );
        }

        int pSrc = GetParentRecursive(c);
        int pDst = GetParentRecursive(v);
        if ( pSrc == pDst ){
            ans = widths[pDst];
            break;
        }
    }

    cout << ans;
    
    return 0;
}