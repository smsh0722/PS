/* NOTE:
아이디어 떠올리는 것이 어려웠다.
BFS인 것은 알았으나, hypertube간 이동을 어떻게 해야 빨리할지 고민했다.
그냥 hypertube, station 둘다 visited 두면 된다.
(아예 합쳐서 hypertube도 station처럼 볼 수도 있다.)

추가로, visited 체크 시점으로 q가 터졌다.
재방문할 일이 전혀 없기 때문에 queue에 넣는 순간 visited 처리해야한다.(vs dijkstra 고민하기)
*/
#include <iostream>
#include <vector>
#include <queue>

using namespace std;

struct Station{
    int station;
    int dist;
};

int N; // num of station
int K; // l of hypertube
int M; // num of hypertubes

vector<vector<int>> hypertubes; // [hypertube No][hyper idx]
vector<vector<int>> stations; // [station No][hyper No];
vector<bool> visited; // [station no]
vector<bool> visitedHypertube;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> M;
    hypertubes.resize(M, vector<int>(K, 0) );
    stations.resize(N+1);
    visitedHypertube.resize(M, false);
    visited.resize(N+1, false);
    for ( int m = 0; m < M; m++ ){ // hypertube no: m
        for ( int k = 0; k < K; k++ ){ // hypertube Idx
            int station;
            cin >> station;
            stations[station].push_back(m);
            hypertubes[m][k] = station;
        }
    }

    int rst = -1;
    queue<Station> q;
    q.push({1,1});
    visited[1] = true;
    while (q.empty() == false ){
        Station s = q.front();
        q.pop();

        if ( s.station == N ){
            rst = s.dist;
            break;
        }

        for ( size_t i = 0; i < stations[s.station].size(); i++ ){
            int h = stations[s.station][i];
            if ( visitedHypertube[h] == true )
                continue;
            visitedHypertube[h] = true;

            for ( size_t j = 0; j < hypertubes[h].size(); j++ ){
                int nextS = hypertubes[h][j];
                if (visited[nextS] == true )
                    continue;
                visited[nextS] = true;
                q.push({nextS, s.dist+1});
            }
        }
    }

    cout << rst;

    return 0;
}