#include <iostream>
#include <vector>
using namespace std;

// # of vertices
int N;
// # of turn
int M;

vector<int> parents;
vector<int> ranks;

int GetParentRecursive( int a )
{
    return parents[a] == a ? a : (parents[a] = GetParentRecursive(parents[a]) );
}

inline int GetParent( int a )
{
    int p = -1;
    while ( p != a ){
        p = a;
        a = parents[a];
    }
    
    return p;
}

void Union( int a, int b )
{
    int pa = GetParentRecursive( a );
    int pb = GetParentRecursive( b );

    if ( ranks[pa] < ranks[pb] ){
        parents[pa] = pb;
    }
    else if ( ranks[pa] > ranks[pb] ){
        parents[pb] = pa;
    }
    else { // ranks[pa] == ranks[pb]
        parents[pb] = pa;
        ranks[pa]++;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    // Init 
    parents.resize(N, 0);
    for ( int i = 0; i < N; i++ )
        parents[i] = i;
    ranks.resize(N, 0);
    // Test each turn
    int ans = 0;
    for ( int mi = 1; mi <= M; mi++ ){
        int a, b;
        cin >> a >> b;
        int pa = GetParentRecursive(a);
        int pb = GetParentRecursive(b);
        if ( pa == pb ){
            ans = mi;
            break;
        }
        else {
            Union(a, b);
        }
    }

    cout << ans;

    return 0;
}