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

void makeSet( const int ca, const int cb, int c2p[], vector<int> p2c[] )
{
    /* parent b to a */
    int pa = c2p[ca];
    int pb = c2p[cb];
    while ( p2c[pb].size() > 0 ){
        int pb_c = p2c[pb].back();
        p2c[pb].pop_back();

        c2p[pb_c] = pa;
        p2c[pa].push_back(pb_c);
    }
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
    /* kruskal */
    {
        int c2p[n_com+1];
        vector<int> p2c[n_com+1];
        for ( int i = 1; i <= n_com; i++ )
            c2p[i] = i;
        for ( int i = 1; i <= n_com; i++ )
            p2c[i].push_back(i);

        qsort( edges, n_edge, sizeof(edge), compare );
        for ( int ei = 0; ei < n_edge; ei++ ){
            int pa = c2p[edges[ei].ca];
            int pb = c2p[edges[ei].cb];
            
            if ( pa != pb ){
                sum += edges[ei].w;
                makeSet( edges[ei].ca, edges[ei].cb, c2p, p2c );
            }
        }
    }
    cout << sum << endl;

    return 0;
}