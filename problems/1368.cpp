#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Edge{
    int v1;
    int v2;
    int w;
};

const int MAX_INT = ~(1<<31);
const int MAX_N = 300;

int N;
vector<int> parent(MAX_N+1, 0); // idx: 0=water, 
vector<Edge> edges;

bool EdgeCompare( const Edge& a, const Edge& b )
{
    return a.w < b.w;
};

int FindParent( int n )
{
    if ( parent[n] == 0 )
        return 0;
    else if  (parent[n] == n )
        return n;
    
    return (parent[n] = FindParent(parent[n]));
}
void Union( int a, int b )
{
    int pa = FindParent(a);
    int pb = FindParent(b);

    if ( pa > pb ){
        int tmp = pb;
        pb = pa;
        pa = tmp;
    }
    parent[pb] = pa;
}  

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Prepare
    cin >> N;
    for ( int n = 1; n <= N; n++ ){
        int w;
        cin >> w;
        edges.push_back(Edge{n,n,w});
    }

    for ( int r = 1; r <= N; r++ ){
        int w;
        for ( int c = 1; c <= N; c++ ){
            cin >> w;
            if ( r < c ){
                edges.push_back(Edge{r, c, w});
            }            
        }
    }
    sort(edges.begin(), edges.end(), EdgeCompare );

    for ( int i = 1; i <= N; i++ ){
        parent[i] = i;
    }

    // Solve
    int count = 0;
    int sum = 0;
    for ( size_t i = 0; i < edges.size() && count < N; i++ ){
        Edge e = edges[i];

        if ( e.v1 == e.v2 ){
            int p = FindParent(e.v1);
            if ( p != 0 ){
                Union( e.v1, 0 );
                sum += e.w;
                count++;
                printf("edge v1: %d, v2: %d, w: %d\n", e.v1, e.v2, e.w); // Debug
            }
        }
        else {
            int p1 = FindParent(e.v1);
            int p2 = FindParent(e.v2);
            if ( p1 != p2 ){
                Union(p1, p2);
                sum += e.w;
                count++;
                
                printf("edge v1: %d, v2: %d, w: %d, p(%d, %d)\n", e.v1, e.v2, e.w, p1, p2); // Debug
            }
        }
    }    
    cout << sum;

    return 0;
}