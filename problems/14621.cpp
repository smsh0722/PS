#include <iostream>
#include <vector>
#include <queue>
using namespace std;

namespace SCHOOL{
    enum eType{
        NONE, M, W
    };
};

struct Road{
    int to;
    int dist;
};

struct RoadCompare{
    bool operator() ( const Road& a, const Road& b )
    {
        return a.dist > b.dist;
    }
};

// # of schools
int N;
// # of roads
int M;

vector<SCHOOL::eType> schools;
vector<vector<Road>> adjList;

int mstSum = 0;
int mstCount = 0;
vector<bool> mst;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    schools.resize(N+1, SCHOOL::eType::NONE);
    for ( int i = 1; i <= N; i++ ){
        char c;
        cin >> c;
        if ( c == 'M' ){
            schools[i] = SCHOOL::eType::M;
        }
        else {//c=='W'
            schools[i] = SCHOOL::eType::W;
        }
    }
    
    adjList.resize(N+1);
    for ( int mi = 0; mi < M; mi++ ){
        int u, v, d;
        cin >> u >> v >> d;
        if ( schools[u] == schools[v] )
            continue;
        // cout << "add: " << u << ", " << v << ", " << d << endl; // DEBUG
        adjList[u].push_back({v,d});
        adjList[v].push_back({u,d});
    }

    mst.resize(N+1, false);
    priority_queue<Road, vector<Road>, RoadCompare> pq;
    pq.push({1,0});
    while ( pq.empty() == false ){
        Road cur = pq.top();
        pq.pop();

        if ( mst[cur.to] == true )
            continue;

        mst[cur.to] = true;
        mstCount++;
        mstSum += cur.dist;

        for ( auto r : adjList[cur.to] ){
            if( mst[r.to] == true )
                continue;
            pq.push({r.to, r.dist});
        }
    }

    // cout << "msCount: " << mstCount << " mstSum: " << mstSum << endl; // DEBUG
    if( mstCount < N )
        cout << -1;
    else 
        cout << mstSum;
        
    return 0;
}