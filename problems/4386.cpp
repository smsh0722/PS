#include <iostream>
#include <vector>
#include <cmath>
#include <algorithm>

using namespace std;

struct Vec2{
    float x, y;
};

struct Edge{
    int a;
    int b;
    float dist;
};

const int MAX_N = 100;
int N;

vector<Vec2> stars;
vector<Edge> edges;
vector<int> parent;
vector<int> treeRank;
bool EdgeCompare( const Edge& a, const Edge& b )
{
    return a.dist < b.dist;
};

int FindParentRecursive( int n )
{
    return parent[n] == n ? n : (parent[n] = FindParentRecursive(parent[n]));
}

void Union( int a, int b )
{
    int pa = FindParentRecursive(a);
    int pb = FindParentRecursive(b);
    if ( pa != pb ){
        if ( treeRank[pa] < treeRank[pb] ){
            parent[pa] = pb;
        }
        else if ( treeRank[pa] > treeRank[pb] ){
            parent[pb] = pa;
        }
        else { // treeRank[pa] == treeRank[pb]
            parent[pa] = pb;
            treeRank[pb]++;
        }
    }
}

int main( void)
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    stars.resize(N);
    parent.resize(N);
    treeRank.resize(N,0);
    for ( int i = 0; i < N; i++ )
        parent[i] = i;

    for ( int i = 0; i < N; i++ ){
        cin >> stars[i].x >> stars[i].y;
    }

    for ( int i = 0; i < N; i++ ){
        for ( int j = i+1; j < N; j++ ){
            float dist = sqrt( pow(stars[i].x-stars[j].x, 2) +
                                pow(stars[i].y-stars[j].y, 2) );           
            edges.push_back(Edge{i,j,dist});
        }
    }
    sort(edges.begin(), edges.end(), EdgeCompare );

    float sum = 0;
    int numOfEdge = 0;
    for ( size_t i = 0; i < edges.size(); i++ ){
        Edge e = edges[i];

        int pa = FindParentRecursive(e.a);
        int pb = FindParentRecursive(e.b);
        if ( pa == pb )
            continue;
        
        Union( e.a, e.b);

        sum += e.dist;
        numOfEdge++;
        if ( numOfEdge == N-1)
            break;
    }

    printf("%.2f\n", sum);

    return 0;
}