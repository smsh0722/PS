#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Bridge{
    int house;
    int weightLimit;
};

struct BridgeCompare{
    bool operator()( const Bridge& a, const Bridge& b )
    {
        return a.weightLimit < b.weightLimit; // w 내림차순
    };
};

const int MAX_INT = ~(1<<31);
const int MAX_N = 100000;
const int MAX_M = 300000;

int N; // num of houses
int M; // num of bridges
int s, e;

vector<vector<Bridge>> adjList(MAX_N+1);
vector<int> dijkstra(MAX_N+1, 0);
priority_queue<Bridge, vector<Bridge>, BridgeCompare> pq;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    cin >> s >> e;
    for ( int m = 0; m < M; m++ ){
        int h1, h2, k;
        cin >> h1 >> h2 >> k;
        adjList[h1].push_back({h2,k});
        adjList[h2].push_back({h1,k});
    }

    // Solve
    dijkstra[s] = MAX_INT;
    pq.push({s, MAX_INT});
    while ( pq.empty() == false ){
        Bridge t = pq.top();
        pq.pop();

        if ( dijkstra[t.house] > t.weightLimit )
            continue;
        
        for ( size_t i = 0; i < adjList[t.house].size(); i++ ){
            Bridge b = adjList[t.house][i];

            int newWeightLimit = min(t.weightLimit, b.weightLimit);
            if ( dijkstra[b.house] < newWeightLimit ){
                dijkstra[b.house] = newWeightLimit;
                pq.push({b.house, newWeightLimit});
            }
        }
    }

    cout << dijkstra[e];

    return 0;
}