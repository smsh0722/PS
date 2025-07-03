#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Vec2{
    int r,c;
};

int R, C;

int main ( void ) 
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> R >> C;

    int cheeseCount = 0;
    vector<vector<int>> wordlMat( R, vector<int>(C, 0) );
    vector<vector<bool>> visited( R, vector<bool>(C, false ));
    for ( int r = 0; r < R ; r++ ){
        for ( int c = 0; c < C; c++ ){
            cin >> wordlMat[r][c];
            cheeseCount += wordlMat[r][c];
        }
    }

    int time = 0;
    int prevCheeseCount = -1;
    queue<Vec2> bfsQ;
    queue<Vec2> exposedCheeseQ;
    bfsQ.push(Vec2{0,0});
    while ( cheeseCount > 0 ){
        time++;
        prevCheeseCount = cheeseCount;

        // phase1: Check New Area
        while ( bfsQ.empty() == false ){
            Vec2 pos = bfsQ.front(); 
            bfsQ.pop();
            
            vector<Vec2> adjList;
            adjList.push_back(Vec2{pos.r-1, pos.c});
            adjList.push_back(Vec2{pos.r+1, pos.c});
            adjList.push_back(Vec2{pos.r, pos.c-1});
            adjList.push_back(Vec2{pos.r, pos.c+1});

            for ( int i = 0; i < 4; i++ ){
                pos = adjList[i];
                if ( 0 <= pos.r && pos.r < R &&
                    0 <= pos.c && pos.c < C &&
                    visited[pos.r][pos.c] == false ){
                    visited[pos.r][pos.c] = true;
                    if ( wordlMat[pos.r][pos.c] == 1 ){ // case1: cheese
                        exposedCheeseQ.push(pos);
                    }
                    else { // case2: air
                        bfsQ.push(pos);
                    }
                }
            }
        }   

        // phase2: Melt Cheese
        while ( exposedCheeseQ.empty() == false ){
            Vec2 pos = exposedCheeseQ.front();
            exposedCheeseQ.pop();

            wordlMat[pos.r][pos.c] = 0;
            bfsQ.push(pos);

            cheeseCount--;
        }
    }

    cout << time << endl    
         << prevCheeseCount << endl;

    return 0;
}