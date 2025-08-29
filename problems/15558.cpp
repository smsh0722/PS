#include <iostream>
#include <vector>
#include <string>
#include <queue>
using namespace std;

struct Next{
    int idx;
    int worldNum;
    int time;
};

// Size of World
int N;
// Size of Jump
int K;

int gameTime = 0;
int idx = 1;
int worldNum = 0;
// worldNum = 0 or 1
string worlds[2];
vector<bool> visited[2];

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;

    cin >> worlds[0];
    cin >> worlds[1];

    worlds[0] = "." + worlds[0];
    worlds[1] = "." + worlds[1];
    visited[0].resize(N+1, false );
    visited[1].resize(N+1, false );

    // Sovle
    bool bFlag = false;
    queue<Next> bfs;
    bfs.push( Next{1,0,0});
    while ( bfs.empty() == false ){
        Next cur = bfs.front();
        bfs.pop();

        // printf("idx %d, world %d, time %d\n", cur.idx, cur.worldNum, cur.time);
        // printf("world time: %d\n", gameTime);
        if ( gameTime >= cur.idx )
            continue;

        int nextIdx = cur.idx + 1;
        int nextWorld = cur.worldNum;
        // Move forward
        if ( nextIdx > N ){
            bFlag = true;
            break;
        }
        else if ( worlds[nextWorld][nextIdx] == '1' && visited[nextWorld][nextIdx] == false ){
            visited[nextWorld][nextIdx] = true;
            bfs.push( Next{nextIdx, nextWorld, cur.time+1} );
        }

        // Move backward
        nextIdx = cur.idx - 1;
        if ( nextIdx > 0 && worlds[nextWorld][nextIdx] == '1' &&  visited[nextWorld][nextIdx] == false ){
            visited[nextWorld][nextIdx] = true;
            bfs.push( Next{nextIdx, nextWorld, cur.time+1} );
        }
        // Move Jump
        nextIdx = cur.idx + K;
        nextWorld = (cur.worldNum + 1) % 2;
        if ( nextIdx > N ){
            bFlag = true;
            break;
        }
        else if ( worlds[nextWorld][nextIdx] == '1' &&  visited[nextWorld][nextIdx] == false ){
            visited[nextWorld][nextIdx] = true;
            bfs.push( Next{nextIdx, nextWorld, cur.time+1} );
        }

        // Time Update
        if ( bfs.empty() == false ){
            gameTime = cur.time < bfs.front().time ? gameTime + 1: gameTime;
        }
    }

    if (bFlag == true )
        cout << 1;
    else 
        cout << 0;

    return 0;
}