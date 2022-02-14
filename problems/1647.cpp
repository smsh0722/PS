/* 1922 네트워크 연결
 * smsh0722
 * 
 * */
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct edge {
    int ca; // computer A
    int cb; // computer B
    int w; // weight
};

int compare( const void* a, const void* b )
{
    edge* aPtr = (edge*)a;
    edge* bPtr = (edge*)b;
    return (aPtr->w - bPtr->w);
}

int findP( const int ca, int c2p[] )
{
    int p = c2p[ca];
    
    if ( p == ca )
        return p;
    else 
        p = findP( p, c2p );
    c2p[ca] = p;
    return p;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    int n_com, n_edge;
    cin >> n_com >> n_edge;
    
    edge edges[n_edge];
    for ( int i = 0; i < n_edge; i++ )
        cin >> edges[i].ca >> edges[i].cb >> edges[i].w;

    int sum = 0;
    int max = 0;
    /* kruskal */
    {
        int c2p[n_com+1];
        for ( int i = 1; i <= n_com; i++ )
            c2p[i] = i;

        qsort( edges, n_edge, sizeof(edge), compare );
        for ( int ei = 0; ei < n_edge; ei++ ){
            int pa = findP( edges[ei].ca, c2p );
            int pb = findP( edges[ei].cb, c2p );
            
            if ( pa != pb ){
                sum += edges[ei].w;
                max = max < edges[ei].w ? edges[ei].w : max;
                c2p[pb] = pa;
            }
        }
    }
    cout << sum - max << "\n";

    return 0;
}