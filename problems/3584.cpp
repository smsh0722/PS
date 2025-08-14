#include <iostream>
#include <vector>
#include <stack>
using namespace std;

int T;

int N;

void GetParents( const vector<int>& tree, stack<int>& parents, int node )
{
    int p = node;
    while ( p != 0 ){
        parents.push(p);
        p = tree[p];
    }
}
int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for ( int t = 0; t < T; t++ ){
        cin >> N;
        vector<int> tree(N+1, 0);
        for ( int i = 0; i < N-1; i++ ){
            int p, c;
            cin >> p >> c;
            tree[c] = p;
        }

        int a, b;
        cin >> a >> b;

        stack<int> parentsOfA;
        stack<int> parentsOfB;
        GetParents( tree, parentsOfA, a );
        GetParents( tree, parentsOfB, b );

        int lca = 0;
        while ( parentsOfA.empty() == false && parentsOfB.empty() == false ){
            if ( parentsOfA.top() != parentsOfB.top() ){
                break;
            }
            lca = parentsOfA.top();
            parentsOfA.pop();
            parentsOfB.pop();
        }

        cout << lca << "\n";
    }
    return 0;
}