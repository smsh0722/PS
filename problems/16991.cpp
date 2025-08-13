#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

const double INF_WEIGHT = ~(1<<31);

struct Vec2{
    int x, y;
};

int fullMask;
int N;

vector<Vec2> cities;
vector<vector<double>> adjMat;
// memo[city][visited] = weight, (w=-1: unsearched)
vector<vector<double>> memo;

double DFS( int city, int visited )
{
    if ( memo[city][visited] != -1 )
        return memo[city][visited];
    
    if ( visited == fullMask ){
        return (memo[city][visited] = adjMat[city][0] );
    }

    double rst = INF_WEIGHT;
    for ( int dst = 1; dst < N; dst++ ){
        int dstMask = (1<<dst);
        double localRst = INF_WEIGHT;
        if ( visited&dstMask )
            continue;

        localRst = DFS(dst, visited|dstMask );
        if ( localRst == INF_WEIGHT )
            continue;
        rst = min(rst, localRst+adjMat[city][dst]);
    }

    return (memo[city][visited] = rst );
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N;

    // Init
    fullMask = (1<<N)-1;
    cities.resize(N);
    adjMat.resize(N, vector<double>(N) );
    memo.resize(N, vector<double>(fullMask+1, -1));

    // Process Input
    for( int i = 0; i < N; i++ ){
        cin >> cities[i].x >> cities[i].y;
    }
    for ( int src = 0; src < N; src++ ){
        for ( int dst = 0; dst < N; dst++ ){
            adjMat[src][dst] = sqrt( pow(cities[src].x-cities[dst].x, 2) + pow(cities[src].y-cities[dst].y, 2) );            
        }
    }

    // DFS
    printf("%.10f\n", DFS(0,1));

    return 0;
}