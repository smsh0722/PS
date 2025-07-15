/* Kruskal's Algorithm
*/
#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

struct Edge{
    int a;
    int b;
    int weight;
};

int V;
int E;

vector<Edge> edges;
vector<int> parent;
vector<int> treeRank;

bool EdgeCompare( const Edge& a, const Edge& b )
{
    return a.weight < b.weight; // weight 오름차순
};

int FindParentRecursive( int n )
{
    // path compression
    return parent[n] == n ? n : (parent[n] = FindParentRecursive(parent[n]));
}

void Union( int a, int b )
{
    int pa = FindParentRecursive(a);
    int pb = FindParentRecursive(b);
    if ( pa!=pb){
        if ( treeRank[pa] < treeRank[pb] ){
            parent[pa] = pb;
        }
        else if ( treeRank[pa] > treeRank[pb] ){
            parent[pb] = pa;
        }
        else {
            parent[pa] = pb;
            treeRank[pb]++; // rank increased
        }
    }
}

int main(void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> V >> E;

    // Init
    edges.resize(E);
    parent.resize(V+1);
    for ( int i = 0; i <= V; i++ )
        parent[i] = i;
    treeRank.resize(V+1, 0);

    // Get edges
    for ( int i = 0; i < E; i++ ){
        cin >> edges[i].a >> edges[i].b >> edges[i].weight;
    }
    sort( edges.begin(), edges.end(), EdgeCompare );

    // Build MST
    int rst = 0;
    int count = 0;
    for( int ei = 0; ei < E; ei++ ){
        Edge e = edges[ei];
        // has cycle?
        int pa = FindParentRecursive(e.a);
        int pb = FindParentRecursive(e.b);
        if ( pa == pb )
            continue;
        // union
        Union( e.a, e.b );
        rst += e.weight;
        count++;
        if ( count == V-1 )
            break;
    }

    if ( count != V-1 )
        cout << "FAILED\n";
    else 
        cout << rst;

    return 0;
}