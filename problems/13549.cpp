#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Node{
    int pos, time;
};

struct NodeComp {
    bool operator()(Node& a, Node& b ){
        return a.time > b.time;
    }
};

const int MAX_INT = ~(1<<31);
const int POS_MAX = 100000;

int N, K; // Position [0, 100000]

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> K;

    vector<int> timeVec(POS_MAX+1, MAX_INT); // []
    {
        priority_queue<Node, vector<Node>, NodeComp> pq;
        pq.push(Node{N, 0});
        timeVec[N] = 0;
        while ( pq.empty() == false ){
            Node node = pq.top();
            pq.pop();

            if (node.time > timeVec[node.pos] )
                continue;
            
            vector<Node> adjList;
            adjList.push_back(Node{node.pos-1, node.time+1});
            adjList.push_back(Node{node.pos+1, node.time+1});
            adjList.push_back(Node{2*node.pos, node.time});
            for ( int i = 0; i < 3; i++ ){
                Node adjNode = adjList[i];
                if ( adjNode.pos < 0 || adjNode.pos > POS_MAX )
                    continue;
                if( timeVec[adjNode.pos] > adjNode.time ){
                    timeVec[adjNode.pos] = adjNode.time;
                    pq.push(adjNode);
                }
            }
        }
    }

    cout << timeVec[K];
}