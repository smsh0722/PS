#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Edge{
    int dst;
    int time;
};
struct DijkstraData{
    int pc;
    int time;
};

struct DijkstraCompare{
    bool operator() (const DijkstraData& a, const DijkstraData& b )
    {
        return a.time > b.time; // 오름차순
    }
};

const int MAX_INT = ~(1<<31);

int N; // num of computer
int M; // num of edge

vector<vector<Edge>> adjList;
vector<DijkstraData> dijkstraTable; // pc: parent, time: time
priority_queue<DijkstraData, vector<DijkstraData>, DijkstraCompare> pq; // pc: cur pc, time: time

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;
    adjList.resize(N+1);
    {
        int comA, comB, cost;
        for ( int i = 0; i < M; i++ ){
            cin >> comA >> comB >> cost;
            adjList[comA].push_back(Edge{comB, cost });
            adjList[comB].push_back(Edge{comA, cost });
        }
    }

    dijkstraTable.resize(N+1, DijkstraData{-1, MAX_INT} );
    dijkstraTable[1] = DijkstraData{1, 0};
    pq.push(DijkstraData{1,0});
    while ( pq.empty() == false ){
        DijkstraData cur = pq.top();
        pq.pop();
        
        if ( dijkstraTable[cur.pc].time < cur.time )
            continue;
        
        for ( size_t i = 0; i < adjList[cur.pc].size(); i++ ){
            int newTime = cur.time + adjList[cur.pc][i].time;

            if ( dijkstraTable[adjList[cur.pc][i].dst].time > newTime ){
                pq.push(DijkstraData{adjList[cur.pc][i].dst, newTime});
                dijkstraTable[adjList[cur.pc][i].dst].time = newTime;
                dijkstraTable[adjList[cur.pc][i].dst].pc = cur.pc;
            }
        }
    }

    cout << N-1 << "\n";
    for ( int pcA = 2; pcA <= N; pcA++ ){
        int pcB = dijkstraTable[pcA].pc;
        cout << pcA << " " << pcB << "\n";
    }

    return 0;
}