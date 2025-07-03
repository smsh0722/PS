/*
dijkstra로 풀었다.
그러나, 인접한 노드간의 거리는 그냥 1이기 때문에 BFS만으로도 최단거리로 도착 할 수 있다.
*/
#include <iostream>
#include <queue>
#include <vector>
#include <string>
using namespace std;

const int MAX_INT = ~(1<<31);

struct Vec2{
    int r, c;
};

struct Distance{
    int normalDist;
    int breakthroughDist;
};

struct Node{
    Vec2 pos;
    int dist;
    bool bIsBreakthrough;
};

struct MyComp{
    bool operator()( Node& a, Node& b ){
        return a.dist > b.dist;
    }
};
int N, M;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;

    vector<vector<char>> worldMat(N, vector<char>(M));
    vector<vector<Distance>> dist(N, vector<Distance>(M, Distance{MAX_INT, MAX_INT}));

    for ( int r = 0; r < N; r++ ){
        string s;
        cin >> s;
        for ( int c = 0; c < M; c++ ){
            worldMat[r][c] = s.at(c);
        }
    }

    dist[0][0] = Distance{1,1};
    priority_queue<Node, vector<Node>, MyComp> pq;
    pq.push( Node{ Vec2{0,0}, 1, false});
    while ( pq.empty() == false ){
        Node node = pq.top();
        pq.pop();
        
        // Check is min node
        if ( node.bIsBreakthrough == true ){
            if( dist[node.pos.r][node.pos.c].breakthroughDist < node.dist)
                continue;
        }   
        else {
            if( dist[node.pos.r][node.pos.c].normalDist < node.dist )
                continue;
        }

        // Test adjNode
        vector<Vec2> adjList;
        adjList.push_back(Vec2{node.pos.r-1, node.pos.c});
        adjList.push_back(Vec2{node.pos.r+1, node.pos.c});
        adjList.push_back(Vec2{node.pos.r, node.pos.c-1});
        adjList.push_back(Vec2{node.pos.r, node.pos.c+1});
        for ( int adjIdx = 0; adjIdx < 4; adjIdx++ ){
            Vec2 pos = adjList[adjIdx];
            if ( pos.r < 0 || pos.r >= N || pos.c < 0 || pos.c >= M )
                continue;

            int newDist = node.dist + 1;
            if ( worldMat[pos.r][pos.c] == '0' ){
                if ( node.bIsBreakthrough == true ){
                    if( dist[pos.r][pos.c].breakthroughDist > newDist ){
                        dist[pos.r][pos.c].breakthroughDist = newDist;
                        pq.push(Node{pos, newDist, true});
                    }
                }
                else {
                    if( dist[pos.r][pos.c].normalDist > newDist ){
                        dist[pos.r][pos.c].normalDist = newDist;
                        pq.push(Node{pos, newDist, false });
                    }
                }
            }
            else { // Wall
                if ( node.bIsBreakthrough == true )
                    continue;
                if ( dist[pos.r][pos.c].breakthroughDist > newDist ){
                    dist[pos.r][pos.c].breakthroughDist = newDist;
                    pq.push(Node{pos, newDist, true });
                }
            }
        }
    }

    if (dist[N-1][M-1].normalDist == MAX_INT && dist[N-1][M-1].breakthroughDist == MAX_INT )
        cout << -1;
    else {
        int rst = dist[N-1][M-1].normalDist;
        rst = rst > dist[N-1][M-1].breakthroughDist ? 
                dist[N-1][M-1].breakthroughDist : rst;
        cout << rst;
    }

    return 0;
}