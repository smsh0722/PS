#include <iostream>
#include <climits>
#include <queue>
#include <vector>
using namespace std;

struct To{
    int dst;
    int w;
};

struct PQNode{
    int v;
    int cost;
};

// Num of vertices
int V;
// Num of Edges
int E;
// Num of Mcdonard
int M;
// Num of Starbuks
int S;
// Max dist to Mcdonard
int x;
// Max dist to Starbuks
int y;

vector<vector<To>> adjList;
vector<bool> IsMcdonard;
vector<bool> IsStarbuks;

vector<int> dijkstraMcdonard;
vector<int> dijkstraStrabuks;


// PQ cost 기준 내림차순 정렬
struct ComparePQNode
{
    bool operator() ( const PQNode& a, const PQNode& b )
    {
        return a. cost > b.cost;
    }
};

void CalculateDijkstra( int startV, vector<bool>& IsStartingPoint, vector<int>& dijkstra)
{
    // Cal Dijk for mc
    dijkstra[startV] = 0;
    priority_queue<PQNode, vector<PQNode>, ComparePQNode> pq;
    pq.push( {startV, 0} );
    while ( pq.empty() == false )
    {
        PQNode top = pq.top();
        pq.pop();

        if ( dijkstra[top.v] < top.cost )
            continue;
        
        for ( size_t i = 0; i < adjList[top.v].size(); i++ ){
            To to = adjList[top.v][i];

            // to == starting Point
            if ( IsStartingPoint[to.dst] == true && dijkstra[to.dst] != 0 ){ // NOTE: dijkstra 체크를 안하면 queue가 터짐.
                dijkstra[to.dst] = 0;
                pq.push({to.dst,0});
                continue;
            }

            int newCost = to.w + top.cost;
            // to => new min
            if ( IsStartingPoint[to.dst] == false && newCost < dijkstra[to.dst] )
            {   
                dijkstra[to.dst] = newCost;
                pq.push( {to.dst, newCost} );
                continue;
            }
        }
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> V >> E;
    adjList.resize(V+1);
    IsMcdonard.resize(V+1, false);
    IsStarbuks.resize(V+1, false);
    dijkstraMcdonard.resize(V+1, INT_MAX );
    dijkstraStrabuks.resize(V+1, INT_MAX );

    for ( int e = 0; e < E; e++ ){
        int a, b, w;
        cin >> a >> b >> w;
        adjList[a].push_back({b,w});
        adjList[b].push_back({a,w});
    }

    int mStart = 0;
    cin >> M >> x;
    for ( int m = 0; m < M; m++ ){
        int pos;
        cin >> pos;
        IsMcdonard[pos] = true;
        mStart = pos;
    }

    int sStart = 0;
    cin >> S >> y;
    for ( int s = 0; s < S; s++ ){
        int pos;
        cin >> pos;
        IsStarbuks[pos] = true;
        sStart = pos;
    }

    // Cal Dijk for mc
    CalculateDijkstra( mStart, IsMcdonard, dijkstraMcdonard );

    // Cal Dijk for star
    CalculateDijkstra( sStart, IsStarbuks, dijkstraStrabuks );

    // Get Ans
    int ans = INT_MAX;
    for ( int v = 1; v <= V; v++ ){
        if ( IsMcdonard[v] || IsStarbuks[v] ) // NOTE: 이런 것 놓치지 말자.
            continue;
        if ( dijkstraMcdonard[v] > x )
            continue;
        if ( dijkstraStrabuks[v] > y )
            continue;
        
        ans = min( ans, dijkstraMcdonard[v] + dijkstraStrabuks[v] );
    }
    if ( ans == INT_MAX )
        cout << -1;
    else 
        cout << ans;
    

    return 0;
}