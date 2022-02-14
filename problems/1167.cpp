#include <iostream>
#include <vector>
using namespace std;

struct edge {
    int child;
    int weight;
};

int postDFS( const vector< vector<edge> >& tree, const int currNode, vector<int>& sum, vector<bool>& visited );

int main( void )
{
    int n; cin >> n;

    vector< vector<edge> > tree(n+1); // 1~n
    {
        for ( int i = 0; i < n; i++ ){
            int p; cin >> p;    
            int tmp; cin >> tmp;
            while ( tmp != -1 ){
                edge e;
                e.child = tmp;
                cin >> e.weight;
                tree[p].push_back(e);
                
                cin >> tmp;
            }
        }
    }

    vector< int > sum(n +1, 0 ); // 1 ~ n
    {
        vector< bool > visited( n + 1, false );
        postDFS( tree, 1, sum, visited );
    }

    int max = 0;
    for ( int i = 0; i < n + 1; i++ ){
        max = max < sum[i] ? sum[i] : max;
    }
    cout << max;

    return 0;
}

int postDFS( const vector< vector<edge> >& tree, const int currNode, vector<int>& sum, vector<bool>& visited )
{
    visited[currNode] = true;

    int max = 0;
    int max2 = 0;
    for ( int idx = 0; idx < tree[currNode].size(); idx++ ){
        const edge& e = tree[currNode][idx];
        if ( visited[e.child] == false ){
            int rst = e.weight + postDFS( tree, e.child, sum, visited );
            if ( rst >= max ){
                max2 = max;
                max = rst;
            }
            else if ( rst > max2 ){
                max2 = rst;
            }
        }
    }

    sum[currNode] = max + max2;
    return max;
}