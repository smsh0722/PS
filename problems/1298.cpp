/* NOTE:
Naive하게 풀면, DFS하며 현 사람의 가능한 노트북 중 하나를 선택해보며 모든 경우를 살펴 볼 수 있다.
그러나 시간 복잡도상 제한이 있다.

반복되는 상황이 발생하기 때문에 축을 (노트북 차지 상태)x(현재 사람) 으로 하여 
unordered_map과 string을 통해서 DP로 풀려고 하였다.
작은 사이즈에서는 실제로 정답에 도달한다.

그러나, 처음에 우려했던 바와 같이 최대 2^100 가지의 노트북 차지 상태가 생기기 때문에 공간 제한이 터져버린다.

따라서 이 방법은 실패이다.
*/
#include <iostream>
#include <vector>
#include <unordered_map>
#include <string>
using namespace std;

// Num of people
int N;
// Num of laptops adj
int M;

// adjList[peopleIdx][idx] = a laptop
vector<vector<int>> adjList;

vector<unordered_map<string,int>> dpMemo;

string state;

inline bool IsOccupied( string& state, int li )
{
    return state[li] == '1';
}

int SolveRecursive( int p )
{
    if ( p > N )
        return 0;
    if ( dpMemo[p].find(state) != dpMemo[p].end() )
        return dpMemo[p][state];

    // First Visit:
    int rst = 0;
        // 가능한 선택 모두 시도해보기
    for ( size_t i = 0; i < adjList[p].size(); i++ ){
        int laptop = adjList[p][i];

        if ( IsOccupied(state, laptop) == true )
            continue;

        state[laptop] = '1';
        rst = max( rst, SolveRecursive(p+1) + 1);
        state[laptop] = '0';
    }
        // 선택 안 해보기
    rst = max( rst, SolveRecursive(p+1) );

    return dpMemo[p][state] = rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;

    adjList.resize(N+1);
    state = string(N+1, '0');
    for ( int i = 0; i < M; i++ ){
        int p, l;
        cin >> p >> l;

        adjList[p].push_back(l);
    }

    dpMemo.resize(N+1);
    cout << SolveRecursive(1);

    return 0;
}