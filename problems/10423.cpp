#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_CITY = 1000;

struct Cable{
    int dst;
    int w;
};

struct CableWAsc{
    bool operator()(const Cable& a, const Cable& b )
    {
        return a.w > b.w;
    };
};

int N; // num of cities
int M; // num of cables
int K; // num of powers
int countConnected = 0;
int sumWeight = 0;

vector<vector<Cable>> adjList(MAX_CITY);
vector<bool> bMST(MAX_CITY, false );
queue<int> powerList;
priority_queue<Cable, vector<Cable>, CableWAsc> pq;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;
    for ( int k = 0; k < K; k++ ){
        int p;
        cin >> p; p--;
        powerList.push(p);
        bMST[p] = true;
        countConnected++;
    }

    for ( int m = 0; m < M; m++ ){
        int u, v, w;
        cin >> u >> v >> w; u--;v--;
        adjList[u].push_back(Cable{v, w});
        adjList[v].push_back(Cable{u, w});
    }

    while ( powerList.empty() == false ){
        int p = powerList.front();
        powerList.pop();
        
        for ( size_t i = 0; i < adjList[p].size(); i++ ){
            if ( bMST[adjList[p][i].dst] == false )
                pq.push(adjList[p][i]);            
        }
    }

    while ( countConnected < N ){
        Cable cable = pq.top();
        pq.pop();

        if ( bMST[cable.dst] == true )
            continue;
        bMST[cable.dst] = true;
        sumWeight += cable.w;
        countConnected++;

        for ( size_t i = 0; i < adjList[cable.dst].size(); i++ ){
            if ( bMST[adjList[cable.dst][i].dst] == false )
                pq.push(adjList[cable.dst][i]);
        }
    }

    cout << sumWeight;

    return 0;
}
