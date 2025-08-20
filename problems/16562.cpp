#include <iostream>
#include <vector> 
using namespace std;

const int MAX_N = 10000;

// Num of students
int N;
// Num of relations
int M;
// Money
int K;

vector<int> costs(MAX_N+1, 0 );
vector<int> parents(MAX_N+1, 0);
vector<bool> visited( MAX_N+1, false );

int ans = 0;

int FindParentsRecursive( int x )
{
    return (parents[x] == x ? x : (parents[x] = FindParentsRecursive(parents[x])));
}
inline void Union( int a, int b )
{
    int pa = FindParentsRecursive(a);
    int pb = FindParentsRecursive(b);
    
    if ( costs[pa] < costs[pb] ){
        parents[pb] = pa;
    }
    else { // costs[pa] >= cost[pb]
        parents[pa] = pb;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M >> K;
    for ( int i = 1; i <= N; i++ ){
        cin >> costs[i];
    }

    // Get Relations
    for ( int i = 1; i <= N; i++ ){
        parents[i] = i;
    }
    for ( int i = 0; i < M; i++ ){
        int a, b;
        cin >> a >> b;

        int pa = FindParentsRecursive(a);
        int pb = FindParentsRecursive(b);
        if ( pa != pb ){
            Union(a, b);
        }
    }

    for ( int i = 0; i <= N; i++ ){ // Debug
        int pi = FindParentsRecursive(i);
        cout << i << "'th parent = " << pi << ", cost = " << costs[pi] << endl;
    }

    // Answer
    for ( int i = 1; i <= N; i++ ){
        int p = FindParentsRecursive(i);
        if ( visited[p] == false ){
            visited[p] = true;
            ans += costs[p];
        }
        visited[i] = true;
    }

    if ( ans > K )
        cout << "Oh no";
    else 
        cout << ans;

    return 0;
}