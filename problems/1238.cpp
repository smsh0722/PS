#include <iostream>
#include <vector>
#include <queue>

using namespace std;

const int MAX_TOWN = 1000;
const int MAX_TIME = ~(1<<31);

struct Road{
    int dst;
    int time;
};


/*
N: num of town
M: num of road(direction)
X: town for party
*/
int N, M, X;

void FindShortestPath( const vector<vector<Road>>& adjList, vector<int>& timeMemo, int src);

struct compare{
    bool operator() (Road& a, Road& b ) const {
        return a.time > b.time;
    }
};

int main (void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    vector<vector<Road>> adjList(MAX_TOWN);
    vector<vector<Road>> adjListReverse(MAX_TOWN);
    vector<int> goingTimeMemo(MAX_TOWN, MAX_TIME);
    vector<int> comingTimeMemo(MAX_TOWN, MAX_TIME);

    cin >> N >> M >> X;
    X--;
    {
        int src, dst, time;
        for ( int i = 0; i < M; i++ ){
            cin >> src >> dst >> time;
            src--; dst--;
            adjList[src].push_back(Road{dst, time});
            adjListReverse[dst].push_back(Road{src,time});
        }
    } 

    FindShortestPath(adjListReverse, goingTimeMemo, X);
    FindShortestPath(adjList, comingTimeMemo, X);    

    int maxTime = -1;
    for ( int i = 0; i < N; i++ ){
        int tmpTime = goingTimeMemo[i] + comingTimeMemo[i];
        if ( maxTime < tmpTime )
            maxTime = tmpTime;
    }

    cout << maxTime << endl;

    return 0;
}

void FindShortestPath( const vector<vector<Road>>& adjList, vector<int>& timeMemo, int src)
{
    priority_queue<Road, vector<Road>, compare> pq;
    pq.push(Road{src, 0});
    timeMemo[src] = 0;

    while (pq.empty() == false ){
        Road r = pq.top();
        pq.pop();
        int src = r.dst;
        for ( size_t i = 0; i < adjList[src].size(); i++ ){
            Road dstR = adjList[src][i];
            int tmpTime = dstR.time + timeMemo[src];
            if ( timeMemo[dstR.dst] > tmpTime ){
                timeMemo[dstR.dst] = tmpTime;
                pq.push(Road{dstR.dst, tmpTime});
            }
        }
    }
}