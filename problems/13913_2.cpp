/* NOTE: BFS
weight가 딱히 없다.(모두 그냥 1)
따라서 단순 BFS로 최단거리 구할 수 있다.
*/
#include <iostream>
#include <vector>
#include <stack>
#include <queue>
using namespace std;

const int MAX_RIGHT_POSITION = 200000;
const int MAX_TIME = 200000;

// Starting Position
int N;
// Destination Position
int K;

vector<int> parents(MAX_RIGHT_POSITION+1, -1 );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    cin >> K;

    queue<int> q;
    q.push(N);
    parents[N] = N;
    while ( q.empty() == false ){
        int cur = q.front();
        q.pop();

        if ( cur > 0 && parents[cur-1] == -1){
            q.push( cur-1);
            parents[cur-1] = cur;
        }
        if ( cur < MAX_RIGHT_POSITION && parents[cur+1] == -1 ){
            q.push(cur+1);
            parents[cur+1] = cur;
        }
        if ( cur*2 <=MAX_RIGHT_POSITION && parents[cur*2] == -1 ){
            q.push(cur*2);
            parents[cur*2] = cur;
        }
    }

    // Answer
    stack<int> s;
    int pos = K;
    while ( pos != N ){
        s.push(pos);
        pos = parents[pos];
    }
    s.push(pos);

    cout << s.size() - 1 << "\n";
    while ( s.empty() == false ){
        cout << s.top() << " ";
        s.pop();
    }

    return 0;
}