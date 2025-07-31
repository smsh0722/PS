/* NOTE:
dijkstra 변형으로 풀었다.
이것도 어려웠다.

다른 풀이로는 parametric search가 있다고 한다.
이에 대해 공부하자
*/
#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Cable{
    int dst;
    int price;
};

struct PQ{
    int pc;
    int freeCount;
    int price;
};

struct PQCompare{
    bool operator()(const PQ& a, const PQ& b )
    {
        if ( a.freeCount == b. freeCount )
            return a.price > b.price; // price 오름차순
        return a.freeCount > b.freeCount; // freeCount 오름차순
    };
};

const int MAX_INT = ~(1<<31);
const int MAX_N = 1000;
const int MAX_P = 10000;
const int MAX_K = 1000;

int N; // num of computers
int P; // num of cables
int K; // num of free

vector<vector<Cable>> adjList( MAX_N+1);
vector<vector<int>> dijkstra(MAX_N+1, vector<int>(MAX_K+1, MAX_INT)); //[pc][freeCount]
priority_queue<PQ, vector<PQ>, PQCompare> pq;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> P >> K;

    for ( int p = 0; p < P; p++ ){
        int a, b, price;
        cin >> a >> b >> price;
        adjList[a].push_back({b, price});
        adjList[b].push_back({a, price});
    }

    for ( int i = 0; i <= K; i++ )
        dijkstra[1][i] = 0;
    
    pq.push( {1, 0, 0});
    while ( pq.empty() == false ){
        PQ top = pq.top();
        pq.pop();

        if ( dijkstra[top.pc][top.freeCount] < top.price )
            continue;
        
        for ( size_t i = 0; i < adjList[top.pc].size(); i++ ){
            Cable cable = adjList[top.pc][i];
            // case 1: no more free
            int newPrice = max(top.price, cable.price);
            if ( dijkstra[cable.dst][top.freeCount] > newPrice ){
                dijkstra[cable.dst][top.freeCount] = newPrice;
                pq.push({cable.dst, top.freeCount, newPrice} );
            }
            // case 2: get more free
            if ( top.freeCount == K ) // already max freeCount
                continue;
            newPrice = min(top.price, cable.price);
            if ( newPrice == cable.price ){
                newPrice = max( dijkstra[top.pc][top.freeCount+1], cable.price);
            }
            if ( dijkstra[cable.dst][top.freeCount+1] > newPrice ){
                dijkstra[cable.dst][top.freeCount+1] = newPrice;
                pq.push({cable.dst, top.freeCount+1, newPrice});
            }
        }
    }

    if ( dijkstra[N][K] == MAX_INT )
        cout << -1;
    else 
        cout << dijkstra[N][K];

    return 0;
}