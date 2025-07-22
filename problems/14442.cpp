#include <iostream>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct Vec2{
    int r, c;
    Vec2 operator+(const Vec2& other ) const{
        return {r+other.r, c +other.c};
    }
};
struct Node{
    Vec2 pos;
    int distance;
    int breakCount;
};

const int MAX_INT = ~(1<<31);
const int MAX_N = 1000;
const int MAX_M = 1000;
const int MAX_K = 10;
const Vec2 moveVec[4] = { {-1,0}, {1,0}, {0, -1}, {0,1} };

int N; // num of row
int M; // num of column
int K; // num of max breakthrough

vector<vector<vector<int>>> memo( MAX_N, 
            vector<vector<int>>( MAX_M, vector<int>(MAX_K+1, MAX_INT ) )); // [r][c][bc]

vector<vector<char>> world(MAX_N, vector<char>(MAX_M, 0));
queue<Node> q;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;

    for ( int r = 0; r < N; r++ ){
        string s;
        cin >> s;
        for ( int c = 0; c < M; c++ ){
            world[r][c] = s.at(c);
        }
    }

    q.push(Node{Vec2{0,0}, 1, 0});
    while ( q.empty() == false ){
        Node node = q.front();
        q.pop();

        if ( memo[node.pos.r][node.pos.c][node.breakCount] <= node.distance )
            continue;
        memo[node.pos.r][node.pos.c][node.breakCount] = node.distance;

        if ( node.pos.r == N-1 && node.pos.c == M-1 ) // end pos
            continue;

        for ( int i = 0; i < 4; i++ ){
            Vec2 adjNode = node.pos + moveVec[i];
            // printf("adjNode(%d,%d)\n", adjNode.r, adjNode.c); // Debug
            if ( adjNode.r < 0 || adjNode.r >= N || adjNode.c < 0 || adjNode.c >= M )
                continue;

            Node nextNode = {adjNode, node.distance+1, node.breakCount};
            if( world[adjNode.r][adjNode.c] == '1' ){
                nextNode.breakCount++;
                if (nextNode.breakCount > K )
                    continue;
            }
            
            if ( memo[nextNode.pos.r][nextNode.pos.c][nextNode.breakCount] < nextNode.distance )
                continue;
            q.push(nextNode);
        }
    }

    // Print Ans
    int min = MAX_INT;
    for ( int i = 0; i <= K; i++ ){
        min = min > memo[N-1][M-1][i] ? memo[N-1][M-1][i] : min;
    }
    if ( min == MAX_INT )
        cout << -1;
    else 
        cout << min;
    
    return 0;
}