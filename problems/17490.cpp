#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Bridge{
    int buildingNum;
    int64_t cost;
};

// Num of Buildings
int N;
// Num of constructions
int M;
// Num of rocks
int64_t K;

vector<Bridge> bridges;

// constructions[i] = construction between i, i+1
vector<bool> constructions;

vector<int> parents;
vector<int> setSizes;

bool CompareBridge( const Bridge& a, const Bridge& b )
{
    if ( a.cost == b.cost )
        return a.buildingNum < b.buildingNum;
    return a.cost < b.cost;
}

int FindParentsRecursive( int a )
{
    return (parents[a] == a ? a : (parents[a] = FindParentsRecursive(parents[a])) );
}

void Union( int a, int b )
{
    int pa = FindParentsRecursive(a);
    int pb = FindParentsRecursive(b);

    if ( pa == pb )
        return ;

    if ( setSizes[pa] == setSizes[pb] ){
        parents[pb] = pa;
        setSizes[pa]++;
    }
    else if ( setSizes[pa] > setSizes[pb] ){
        parents[pb] = pa;
    }
    else { // setSizes[pa] < setSize[pb]
        parents[pa] = pb;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // Get N, M, K
    cin >> N >> M >> K;
    bridges.resize(N);
    constructions.resize(N+1, false );
    parents.resize(N+1, 0);
    setSizes.resize(N+1, 0);

    // Get costs
    for ( int i = 0; i < N; i++ ){
        int64_t cost;
        cin >> cost;
        bridges[i] = {i+1, cost };
    }
    sort(bridges.begin(), bridges.end(), CompareBridge );

    // Get constructions 
    for ( int i = 0; i < M; i++ ){
        int a, b;
        cin >> a >> b;
        if ( a > b )
            swap(a, b);
        if ( a == 1 && b == N )
            constructions[b] = true;
        else 
            constructions[a] = true;
    }
    
    // Bulid Set
    for ( int i = 1; i <= N; i++ )
        parents[i] = i;
    for ( int i = 1; i <= N; i++ ){
        if ( constructions[i] == true )
            continue;
        int j = i == N ? 1 : i+1;
        Union(i, j);
    }

    // for ( int i = 1; i <= N; i++ ) // DEBUG
    //     printf( "%d'th parent: %d\n", i, FindParentsRecursive(i) ); 
    
    // Solve
    int64_t costSum = 0;
    vector<bool> visited(N+1, false );
    for ( int i = 0; i < N; i++ ){
        Bridge b = bridges[i];
        int parent = FindParentsRecursive(b.buildingNum);
        if ( visited[parent] != true ){
            // printf("link bridge %d, cost: %d\n", b.buildingNum, b.cost); // DEBUG
            costSum += b.cost;
            visited[parent] = true;
        }
        visited[b.buildingNum] = true;
    }
    
    if ( M <= 1 )
         cout << "YES\n";
    else if ( costSum > K )
        cout << "NO\n";
    else 
        cout << "YES\n";

    return 0;
}