/*
disjoint set
union by size
*/
#include <iostream>
#include <vector>
using namespace std;

const int MAX_ROBOT = 1000000;

int N;

vector<int> parents( MAX_ROBOT+1, -1 );
vector<int> dsSize( MAX_ROBOT+1, 1 );

int GetParentsRecursive( int a )
{
    return parents[a] == a ? a : (parents[a] = GetParentsRecursive(parents[a]) );
}

void Union( int a, int b )
{
    int pa = GetParentsRecursive(a);
    int pb = GetParentsRecursive(b);

    if ( pa == pb )
        return; 

    if ( dsSize[pa] < dsSize[pb] ){
        parents[pa] = pb;
        dsSize[pb] = dsSize[pa] + dsSize[pb];
    }
    else if ( dsSize[pa] > dsSize[pb] ){
        parents[pb] = pa;
        dsSize[pa] = dsSize[pb] + dsSize[pa];
    }
    else { // dsSize[pa] == dsSize[pb]
        parents[pb] = pa;
        dsSize[pa] = dsSize[pb] + dsSize[pa];
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    for ( int i = 0; i <= MAX_ROBOT; i++ ){
        parents[i] = i;
    }

    cin >> N;
    for ( int ni = 0; ni < N; ni++ ){
        char opt;
        cin >> opt;
        if ( opt == 'I' ){
            int a, b;
            cin >> a >> b;
            Union(a, b );
        }   
        else { // opt == 'Q'
            int c;
            cin >> c;
            int pc = GetParentsRecursive(c);
            cout << dsSize[pc] << "\n";
        }
    }

    return 0;
}