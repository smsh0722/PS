#include <iostream>
#include <unordered_map>
#include <vector>
#include <queue>
#include <string>
using namespace std;

struct BFS{
    int code;
    int dist;
};
struct MinDist{
    int p;
    int dist;
};

const int INF = INT32_MAX;

// # of codes
int N;
// len of code
int K;

// codes[code] = idx
unordered_map<int,int> codes;
// minDist[idx] = {p, dist}
vector<MinDist> minDist;

queue<BFS> bfs;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K;
    for ( int ni = 1; ni <= N; ni++ ){
        string sCode;
        cin >> sCode;
        int code = 0;
        for ( auto c: sCode ){
            code <<= 1;
            code ^= c == '1' ? 1 : 0;
        }
        codes[code] = ni;

        if (ni == 1 ){
            bfs.push({code, 1});
        }
    }

    minDist.resize(N+1, MinDist{0,INF});
    minDist[1] = {0,1};
    while (bfs.empty() == false ){
        BFS cur = bfs.front();
        bfs.pop();
        int curIdx = codes[cur.code];

        for ( int i = 0; i < K; i++ ){
            int mask = 1<<i;
            int adjCode = cur.code^mask;

            // cout << "adj cand: " << adjCode << endl;// DEBUG
            if ( codes.find(adjCode) == codes.end() )
                continue;

            int adjIdx = codes[adjCode];
            int newDist = cur.dist + 1;
            // cout << "adjCode: " << adjCode << " adjidx: " << adjIdx << " nexDist: " << newDist << endl; // DEBUG
            if ( minDist[adjIdx].dist > newDist ){
                bfs.push({adjCode, newDist});
                minDist[adjIdx] = { curIdx, newDist};
            }
        }
    }

    int Q;
    cin >> Q;
    for ( int qi = 0; qi < Q; qi++ ){
        int dst;
        cin >> dst;
        if ( minDist[dst].dist == INF )
            cout << -1;
        else {
            string ans = "";
            int cur = dst;
            while ( cur != 0 ){
                ans = to_string(cur) + " " + ans;
                cur = minDist[cur].p;
            }
            cout << ans;
        }
        cout << "\n";
    } 

    return 0;
}