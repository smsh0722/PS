/* NOTE:
단순 BFS로는 깊이를 제한할 수 없다고 생각해 greedy한 방법을 모색했다.

그러나, 상태를 저장하며 BFS를 하면 됐다.

항상 단순한 Brute Force 에서 시작해 개선해서 가능한 지 살펴보자.
그래도 안 나오는 경우에 Naive한 방법에서 패턴이나 조건을 찾아내자.
*/
#include <iostream>
#include <string>
#include <unordered_map>
#include <queue>

using namespace std;


struct Node{
    string puzzle;
    int count;
};

struct Vec2{
    int r, c;
    Vec2 operator+(const Vec2& other ) const {
        return {r+other.r, c+other.c};
    };
};

const string ANS = "123456780";
const vector<Vec2> moveVel = { {-1,0}, {1,0}, {0,-1}, {0,1} };

unordered_map<string,int> visited;
queue<Node> q;

void GetAdjList( const string& puzzle, vector<string>& adjList )
{
    int i0;
    for ( i0 = 0; i0 <= 9; i0++ ){
        if( puzzle.at(i0) == '0' ){
            break;
        }
    }

    Vec2 pos0 = Vec2{ i0/3, i0%3};
    for ( int i = 0; i < 4; i++ ){
        Vec2 newPos = pos0 + moveVel[i];
        if ( newPos.r < 0 || newPos.r >= 3 || newPos.c < 0 || newPos.c >= 3 )
            continue;
        int iNew = newPos.r * 3 + newPos.c;
        char tmp = puzzle.at(iNew);
        string s = puzzle;
        s[iNew] = '0';
        s[i0] = tmp;
        adjList.push_back(s);

        /*
        for ( int i = 0; i < 9; i++ ){ // debug
            if ( i % 3 == 0 )
                printf("\n");
            printf( "%c ", s[i] );
        } printf("\n");
        */
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    string puzzle;
    for( int i = 0; i < 9; i++ ){
        int a;
        cin >> a;
        puzzle += to_string(a);
    }

    q.push( Node{ puzzle, 0 } );

    int rst = -1;
    while ( q.empty() == false && rst == -1){
        Node node = q.front(); 
        q.pop();

        if( node.puzzle == ANS ){
            rst = node.count;
            break;
        }

        if ( visited.find(node.puzzle) != visited.end() ) // already visited
            continue;
        visited[node.puzzle] = node.count;

        // Get adjList
        vector<string> adjList;
        GetAdjList( node.puzzle, adjList);

        for ( size_t i = 0; i < adjList.size(); i++ ){
            string newPuzzle = adjList[i];

            if ( visited.find(newPuzzle) != visited.end() )
                continue;

            // BFS adjList
            q.push(Node{newPuzzle, node.count+1});
        }
    }

    cout << rst;

    return 0;
}