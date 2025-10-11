/* NOTE:

핵심 아이디어는 일단 

disjointset을 사용하는 것이다.(LCA까지 생각할 필요는 없고 연결 여부만 판단하면 되기 때문.)

엣지 하나를 제거할 때, 자손들의 세트 정보를 모두 갱신해주어야하기 때문에 O(N)이 걸린다.
N <= 3000, Q <=200,000개로 시간 내로 가능할 것으로 봤다.

그러나, Q+(N-1)개의 쿼리가 들어온다는 점, N,Q<=200,000 이라는 점을 놓치고 있었다.
따라서 단순히 온라인 쿼리로 풀면 틀린다.

해결책은 _2 풀이를 참고
*/
#include <iostream>
#include <vector>
#include <set>
#include <queue>
using namespace std;

vector<set<int>> childs;
vector<int> parentsOfVertices;

// # of vertices
int N;
// # of Queries
int Q;

vector<int> parents;

int FindParentRecursive( int a )
{
    return parents[a] == a ? a : ( parents[a] = FindParentRecursive(parents[a]) );
}

inline void Union( int p, int c )
{
    parents[c] = p;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;
    childs.resize(N+1);
    parentsOfVertices.resize(N+1,1);
    parents.resize(N+1, 1);
    for ( int i = 2; i <= N; i++ ){
        int p;
        cin >> p;
        childs[p].insert(i);
        parentsOfVertices[i] = p;
        Union(p, i);
    }

    // Answer queries
    for ( int qi = 0; qi < Q+(N-1); qi++ ){
        int x;
        cin >> x;
        if ( x == 0 ){
            int u;
            cin >> u;
            childs[parentsOfVertices[u]].erase(u);
            parents[u] = u;
            // 하위 nodes의 set u로 변경
            vector<bool> visited(N+1, false);
            queue<int> q;
            q.push(u);
            visited[u] = true;
            while ( q.empty() == false ){
                int p = q.front();
                q.pop();

                for ( auto c : childs[p] ){
                    if ( visited[c] == true)
                        continue;
                    Union( u, c );

                    q.push(c);
                    visited[c] = true;
                }
            }
        }
        else { // x == 1
            int a, b;
            cin >> a >> b;
            int pa = FindParentRecursive(a);
            int pb = FindParentRecursive(b);
            if ( pa == pb )
                cout << "YES\n";
            else 
                cout << "NO\n";
        }
    }
    return 0;
}