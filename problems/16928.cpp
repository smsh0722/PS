/* 16928
 * smsh0722
 * 뱀과 사다리 게임
 * */
#include <iostream>
#include <queue>
using namespace std;

struct Node{
    int count;
    int cellNum;
};
int main( void )
{
    int N; // # of ladder
    int M; // # of snakes
    cin >> N >> M;

    int map[101] = { 0 };
    for ( int i = 0; i <= 100; i++ )
        map[i] = i;

    // Input
    {
        int src, dst;
        for ( int i = 0; i < N + M; i++ ){
            cin >> src >> dst;
            map[src] = dst;
        }
    }

    // BFS
    int ans = 0;
    bool visited[101] = { false };
    queue<Node> Q;
    Q.push( Node{ 0, 1 } );
    while ( Q.empty() == false ){
        Node curNode = Q.front(); Q.pop();

        ans += curNode.count - ans; // update ans

        if ( curNode.cellNum == 100 )
            break;

        for ( int dice = 1; dice <= 6; dice++ ){
            int nextDst = curNode.cellNum + dice;

            if ( nextDst > 100 )
                break;
        
            nextDst = map[nextDst];

            if ( visited[nextDst] == true )
                continue;
            
            Q.push( Node{ curNode.count + 1, nextDst} );
            visited[nextDst] = true;
        }
    }

    cout << ans;
    return 0;
}