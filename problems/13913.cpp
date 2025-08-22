/* NOTE: Dijkstra
다익스트라로 풀긴 했지만, weight 가 없기 때문에, 단순 BFS 가 낫다.
*/
#include <iostream>
#include <vector>
#include <queue>
#include <stack>
using namespace std;

const int MAX_RIGHT_POSITION = 200000;
const int MAX_TIME = 200000;

struct Memo{
    int pos;
    int time;
};
struct ComparePQ{
    bool operator()( const Memo& a, const Memo& b )
    {
        return a.time > b.time;
    }
};

// Starting Position
int N;
// Destination Position
int K;

vector<Memo> memo( MAX_RIGHT_POSITION+1, {MAX_TIME, MAX_TIME} );

priority_queue<Memo, vector<Memo>, ComparePQ> pq;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    cin >> K;

    pq.push({N, 0});
    memo[N] = {N, 0};
    while ( pq.empty() == false ){
        Memo tMemo = pq.top();
        pq.pop();

        if ( memo[tMemo.pos].time < tMemo.time )
            continue;

        if ( tMemo.pos > 0 ){
            int dst = tMemo.pos-1;
            int newTime = tMemo.time+1;
            if ( memo[dst].time > newTime ){
                memo[dst] = {tMemo.pos, newTime};
                pq.push({dst, newTime});
            }
        }
        if ( tMemo.pos < MAX_RIGHT_POSITION ){
            int dst = tMemo.pos+1;
            int newTime = tMemo.time+1;
            if ( memo[dst].time > newTime ){
                memo[dst] = {tMemo.pos, newTime};
                pq.push({dst, newTime});
            }
        }
        if ( tMemo.pos*2 <= MAX_RIGHT_POSITION){
            int dst = tMemo.pos*2;
            int newTime = tMemo.time+1;
            if ( memo[dst].time > newTime ){
                memo[dst] = {tMemo.pos, newTime};
                pq.push({dst, newTime});
            }
        }
    }

    cout << memo[K].time << "\n";
    stack<int> ans;
    int pos = K;
    while ( pos != N ){
        ans.push(pos);
        pos = memo[pos].pos;
    }
    ans.push(pos);

    while ( ans.empty() == false ){
        int pos = ans.top();
        ans.pop();
        cout << pos << " ";
    }

    return 0;
}