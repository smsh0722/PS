#include <iostream>
#include <vector>
using namespace std;

// # of workers
int n;
// # of compliment
int m;

vector<vector<int>> children;
vector<int> sums;

void DFS( int worker, int sum )
{
    sums[worker] += sum;
    sum = sums[worker];
    for ( auto child : children[worker] ){
        DFS( child, sum );
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> n >> m;
    children.resize(n+1);
    for ( int i = 1; i <= n; i++ ){
        int p;
        cin >> p;
        if ( p == -1 )
            continue;
        children[p].push_back(i);
    }

    sums.resize(n+1, 0);
    for ( int mi = 0; mi < m; mi++ ){
        int i, w;
        cin >> i >> w;
        sums[i] += w;
    }
    
    // DFS
    DFS(1, 0);

    // Ans
    for ( int i = 1; i <= n; i++ ){
        cout << sums[i] << " ";
    }

    return 0;
}