#include <iostream>
#include <vector>
#include <queue>
using namespace std;

struct Vec2{
    int r, c;
};

int N; // NxN world
int M; // num of lights

vector<vector<vector<Vec2>>> buttons;
vector<vector<bool>> visited;
vector<vector<bool>> bAdj;
vector<vector<bool>> bLight;
queue<Vec2> graphQ;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> N >> M;
    buttons.resize(N, vector<vector<Vec2>>(N));
    bAdj.resize(N, vector<bool>(N, false ));
    bLight.resize(N, vector<bool>(N, false ));
    visited.resize(N, vector<bool>(N, false ));
    for ( int m = 0; m < M; m++ ){
        int x, y, a, b;
        cin >> x >> y >> a >> b;
        x--;y--;a--;b--;
        buttons[x][y].push_back(Vec2{a,b});
    }

    int countLights = 1;
    {
        bAdj[0][0] = true;
        bLight[0][0] = true;
        graphQ.push(Vec2{0,0});
        while ( graphQ.empty() == false ){
            Vec2 node = graphQ.front(); 
            graphQ.pop();
            if ( visited[node.r][node.c] == true )
                continue;

            // turn true visited
            visited[node.r][node.c] = true;

            // turn true lights
            for ( size_t i = 0; i < buttons[node.r][node.c].size(); i++ ){
                Vec2 trgRoom = buttons[node.r][node.c][i];
                if ( bLight[trgRoom.r][trgRoom.c] == false ){
                    countLights++;
                    bLight[trgRoom.r][trgRoom.c] = true;
                    if ( bAdj[trgRoom.r][trgRoom.c] == true )
                        graphQ.push(trgRoom);
                }
            }

            // turn true adjNode
            vector<Vec2> adjList;
            adjList.push_back(Vec2{node.r-1, node.c});
            adjList.push_back(Vec2{node.r+1, node.c});
            adjList.push_back(Vec2{node.r, node.c-1});
            adjList.push_back(Vec2{node.r, node.c+1});
            for ( int i = 0; i < 4; i++ ){
                Vec2 adjNode = adjList[i];
                if ( adjNode.r < 0 || adjNode.r >= N || adjNode.c < 0 || adjNode.c >= N )
                    continue;
                bAdj[adjNode.r][adjNode.c] = true;
                if ( bLight[adjNode.r][adjNode.c] == true )
                    graphQ.push(adjNode);
            }
        }
    }

    /*
    cout << "adj\n";
    for ( int r= 0; r < N; r++ ){
        for ( int c = 0; c < N; c++ ){
            cout << bAdj[r][c] << " ";
        } cout << endl;
    }
    cout << "light\n";
    for ( int r= 0; r < N; r++ ){
        for ( int c = 0; c < N; c++ ){
            cout << bLight[r][c] << " ";
        } cout << endl;
    }
*/
    cout << countLights;

    return 0;
}