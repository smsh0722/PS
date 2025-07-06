#include <iostream>
#include <vector>
#include <string>

using namespace std;

struct Vec2{
    int r, c;
    bool operator==(const Vec2& other ) const {
        return (r==other.r)&&(c==other.c);
    }
};

const int MAX_NM = 50;
const int NUM_OF_ALPHABET = 26;

int N, M; // NxM board

vector<vector<char>> board(MAX_NM, vector<char>(MAX_NM));
vector<vector<Vec2>> sPoints(NUM_OF_ALPHABET);

bool HasCycleRecursive( vector<vector<bool>>& visited, const Vec2& parent, const Vec2& cur );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    {
        string s;
        for ( int r = 0; r < N; r++ ){
            cin >> s;
            for ( int c = 0; c < M; c++ ){
                board[r][c] = s.at(c);
                int cIdx = s.at(c) - 'A';
                sPoints[cIdx].push_back(Vec2{r,c});
            }
        }
    }

    for ( int i = 0; i < NUM_OF_ALPHABET; i++ ){
        vector<vector<bool>> visited(N, vector<bool>(M,false));
        for ( size_t j = 0; j < sPoints[i].size(); j++ ){
            Vec2 sPoint = sPoints[i][j];
            if ( visited[sPoint.r][sPoint.c] == true )
                continue;
            if ( HasCycleRecursive( visited, Vec2{-1,-1}, sPoint ) == true ){
                cout << "Yes";
                return 0;
            }
        }
    }

    cout << "No";
    return 0;
}

bool HasCycleRecursive( vector<vector<bool>>& visited, const Vec2& parent, const Vec2& cur )
{
    visited[cur.r][cur.c] = true;

    vector<Vec2> adjList;
    adjList.push_back(Vec2{cur.r-1, cur.c});
    adjList.push_back(Vec2{cur.r+1, cur.c});
    adjList.push_back(Vec2{cur.r, cur.c-1});
    adjList.push_back(Vec2{cur.r, cur.c+1});

    for ( int i = 0; i < 4; i++ ){
        Vec2 adjNode = adjList[i];

        if ( adjNode == parent )
            continue;
        if ( adjNode.r < 0 || adjNode.r >= N || adjNode.c < 0 || adjNode.c >= M )
            continue;
        if ( board[cur.r][cur.c] != board[adjNode.r][adjNode.c] )
            continue;

        if ( visited[adjNode.r][adjNode.c] == true )
            return true;
        else{
            if ( HasCycleRecursive(visited, cur, adjNode) == true )
                return true;
        }
    }

    return false;
}