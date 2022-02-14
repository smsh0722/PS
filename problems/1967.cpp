#include <iostream>
#include <vector>
using namespace std;

struct edge {
    int child;
    int weight;
};

int postDFS( const vector< vector<edge> >& tree, const int currNode, vector<int>& sum );

int main( void )
{
    int n; cin >> n;

    vector< vector<edge> > tree(n+1); // 1~n
    {
        for ( int i = 0; i < n - 1; i++ ){
            int p;
            edge e;
            cin >> p >> e.child >> e.weight;       
            tree[p].push_back(e);
        }
    }

    vector< int > sum(n +1, 0 ); // 1 ~ n
    {
        postDFS( tree, 1, sum );
    }

    int max = 0;
    for ( int i = 0; i < n + 1; i++ ){
        max = max < sum[i] ? sum[i] : max;
    }
    cout << max;

    return 0;
}

int postDFS( const vector< vector<edge> >& tree, const int currNode, vector<int>& sum )
{
    int max = 0;
    int max2 = 0;
    for ( int idx = 0; idx < tree[currNode].size(); idx++ ){
        const edge& e = tree[currNode][idx];

        int rst = e.weight + postDFS( tree, e.child, sum );
        if ( rst >= max ){
            max2 = max;
            max = rst;
        }
        else if ( rst > max2 ){
            max2 = rst;
        }
    }

    sum[currNode] = max + max2;
    return max;
}