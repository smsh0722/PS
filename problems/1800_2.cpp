#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_OVERCOUNT = INT32_MAX;
const int INF_COST = 1000001;

struct Cable{
    int to;
    int cost;
};

struct Node {
    int node;
    int count;
};
struct CompareNode{
    bool operator()( const Node& a, const Node& b)
    {
        return a.count > b.count; // count asc
    }
};

// Num of students
int N;
// Num of cables
int P;
// num of free
int K;

// adjList[stu#][cable#] = cable
vector<vector<Cable>> adjList;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> P >> K;
    adjList.resize(N+1);
    for ( int pi = 0; pi < P; pi++ ){
        int sa, sb, c;
        cin >> sa >> sb >> c;

        adjList[sa].push_back( {sb, c} );
        adjList[sb].push_back( {sa, c} );
    }

    // parametric + dijkstra
    int ans = INF_COST;
    int l = 0; // NOTE: 1로 두어 일부 틀렸음. 처음부터 사례 조사를 잘 했거나, l을 설정할 때 한번 더 고민 했어야 함.
    int r = 1000000;
    while ( l <= r ){
        int mid = (r-l)/2 + l;

        // dijkstra[stu#] = overCount
        vector<int> dijkstra(N+1, MAX_OVERCOUNT);
        priority_queue<Node, vector<Node>, CompareNode> pq;
        
        // Do dijkstra
        pq.push( {1,0} );
        dijkstra[1] = 0; 
        while ( pq.empty() == false ){
            Node top = pq.top();
            pq.pop();

            if ( top.count > dijkstra[top.node] )
                continue;
            
            for ( size_t i = 0; i < adjList[top.node].size(); i++ ){
                Cable cable = adjList[top.node][i];

                int newCount = int( cable.cost > mid ) + top.count;
                if ( newCount < dijkstra[cable.to] ){
                    dijkstra[cable.to] = newCount;
                    pq.push( { cable.to, newCount } );
                }
            }
        }

        // param search
        if ( dijkstra[N] <= K ){
            ans = min(ans, mid);
            r = mid - 1;
        }
        else { // dijkstra[N] > K
            l = mid + 1;
        }
    }

    // answer
    if ( ans == INF_COST )
        cout << -1;
    else
        cout << ans;
    return 0;
}