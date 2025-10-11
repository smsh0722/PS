/* NOTE: sol

하나의 엣지를 제거할 때 O(N)의 시간이 걸린다. 
쿼리를 빠르게 처리하기 위해 고민해야한다.

1-2-3-4 이런 tree가 있다고 해보자.
쿼리가 2, 3, 4 순서로 edge를 제거하라고 연석적으로 들어올 때,
그대로 적용하면 느리다, 4, 3, 2 순서로 제거하는 것이 더 빠를 것 같다.
그러나, 제거와 연결 확인 쿼리가 교차하는 경우 불가능한 풀이이다.

사실 키 포인트는 엣지 제거의 수가 N-1개라는 점이다.
모든 엣지를 제거한다는 뜻이고 마지막엔 모든 정점이 분리된다.
거꾸로 연결하면 어떨까? 
엣지 제거는 자손들의 세트 정보까지 모두 갱신해주어야 했다.
그러나, 연결은 직접적인 두 정점만 연결하면 된다.
이때 경로압축을 적용한 경우 O(a(N)) 으로 거의 O(1)이다.
따라서, 오프라인 쿼리를 통해 문제를 해결할 수 있다.
*/
#include <iostream>
#include <vector>
#include <stack>
using namespace std; 

struct Query{
    int x, a, b;
};

// # of vertices
int N;
// # of Queries
int Q;

vector<int> parents;

vector<int> parentOfSets;
vector<int> ranks;

stack<bool> answers;

int FindParentRecursive( int a )
{
    return parentOfSets[a] == a ? a : ( parentOfSets[a] = FindParentRecursive(parentOfSets[a]));
}

void Union ( int a, int b )
{
    int pa = FindParentRecursive(a);
    int pb = FindParentRecursive(b);

    if ( ranks[pa] < ranks[pb] ){
        parentOfSets[pa] = pb;
    }
    else if ( ranks[pa] > ranks[pb] ){
        parentOfSets[pb] = pa;
    }
    else {// ranks[pa] == ranks[pb] 
        parentOfSets[pb] = pa;
        ranks[pa]++;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> Q;
    // Save Parent of each node
    parents.resize(N+1, 1);
    for ( int i = 2; i <= N; i++ ){
        cin >> parents[i];
    }

    // Save queries for offline queries
    vector<Query> queries (Q+(N-1), {-1,-1,-1});
    for ( int qi = 0; qi < Q+(N-1); qi++ ){
        int x;
        cin >> x;
        if ( x == 0 ){
            queries[qi].x = 0;
            cin >> queries[qi].a;
        }
        else { // x == 1
            queries[qi].x = 1;
            cin >> queries[qi].a >> queries[qi].b;
        }
    }

    // Init set
    ranks.resize(N+1, 0);
    parentOfSets.resize(N+1,1);
    for ( int v = 2; v <= N; v++ )
        parentOfSets[v] = v;

    // Calculate Answer reversely
    for ( int qi = queries.size()-1; qi>=0; qi-- ){
        Query q = queries[qi];
        if ( q.x == 0 ){
            int c = q.a;
            int p = parents[c];
            Union(p, c);
        }   
        else { // q.x == 1
            int pa = FindParentRecursive(q.a);
            int pb = FindParentRecursive(q.b);
            if ( pa == pb ) 
                answers.push(true);
            else 
                answers.push(false);
        }
    }

    // Anwer
    while ( answers.empty() == false ){
        bool ans = answers.top();
        answers.pop();

        cout << ((ans == true) ? "YES\n" : "NO\n");
    }

    return 0;
}