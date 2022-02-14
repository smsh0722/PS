/* 1922 네트워크 연결
 * smsh0722
 * 
 * */
#include <iostream>
#include <vector>
#include <cstdlib>
using namespace std;

struct edge {
    int e1;
    int e2;
    int w;
};

int compare( const void* a, const void* b )
{
    edge* aPtr = (edge*)a;
    edge* bPtr = (edge*)b;
    return (aPtr->w - bPtr->w);
}

bool isCycle( vector<int> adjList[], const int src, const int dst, bool comFlag[] )
{
    comFlag[dst] = true;
    for ( int i = 0; i < adjList[dst].size(); i++ ){
        int trg = adjList[dst][i];
        if ( trg != src ){
            if ( comFlag[trg] == true )
                return true;
            bool result = isCycle( adjList, dst, trg, comFlag );
            if ( result == true )
                return true;
        }
    }
    return false;
}

int main( void )
{
    int n_com, n_edge;
    cin >> n_com >> n_edge;
    
    edge edges[n_edge];
    for ( int i = 0; i < n_edge; i++ )
        cin >> edges[i].e1 >> edges[i].e2 >> edges[i].w;
    qsort( edges, n_edge, sizeof(edge), compare );

    vector<int> adjList[n_com+1];
    int sum = 0;
    for ( int ei = 0; ei < n_edge; ei++ ){
        /* Add weight */
        sum += edges[ei].w;
        /* Add edge */
        int e1 = edges[ei].e1;
        int e2 = edges[ei].e2;
        adjList[e1].push_back(e2);
        adjList[e2].push_back(e1);
        
        /* cycle check */
        bool comFlag[n_com+1] = {false};
        if ( isCycle( adjList, -1, e1, comFlag ) == true ){
            /* detach edge and weight */
            sum -= edges[ei].w;
            adjList[e1].pop_back();
            adjList[e2].pop_back();
        }
    }
    
    cout << sum << endl;

    return 0;
}