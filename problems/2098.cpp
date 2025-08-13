/* NOTE:
1) memoization 방식에서, 불가능한 것과 방문하지 않은 걸 명확히 구분하자.
둘 다 같은 MAX_INT로 했다가 틀렸다.

2) N개를 모두 방문한 걸 idx로 쓰기 위해선,(1<<N)크기 배열을 설정해야, 의도한 [0,(1<<N)-1] 가능
실수로 (1<<N)-1 크기로 세팅함.
*/
#include <iostream>
#include <vector>
#include <string>
using namespace std;

const int MAX_ROW = 16;
const int MAX_COL = (1<<16)-1;
const int MAX_INT = ~(1<<31);

int N;
int endMask;

// City: 0 ~ (N-1)
// adjMat[src][dst] = weight
vector<vector<int>> adjMat;

// table[city][visited(bitmask)] = min Weigt sum
vector<vector<int>> dpMemo(MAX_ROW, vector<int>(MAX_COL+1, -1));

int SearchPathRecursive( int city, int visited )
{
    // Base
    if ( dpMemo[city][visited] != -1 )  
        return dpMemo[city][visited];

    // DFS
    if ( visited == endMask ){
        // printf("city: %d, visited: %d\n", city, visited);
        if ( adjMat[city][0] == 0 )
            return MAX_INT;
        else 
            return (dpMemo[city][visited] = adjMat[city][0]);
    }

    int minWeight = MAX_INT;
    for ( int dst = 1; dst < N; dst++ ){
        int mask = 1<<dst;
        int newWeight = MAX_INT;
        if ( (visited&mask)>0 || (adjMat[city][dst] == 0) )
            continue;

        if ( (newWeight = SearchPathRecursive(dst, visited|mask ) ) == MAX_INT)
            continue;

        newWeight += adjMat[city][dst];
        minWeight = min(minWeight, newWeight);
    }

    // save 
    return (dpMemo[city][visited] = minWeight);
}   

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    // for ( int i = 0; i < 16; i++ ){
    //     for ( int j = 0; j < 16; j++ ){
    //         if ( i == j )
    //             cout << 0 << " ";
    //         else
    //             cout << 1 << " ";
    //     }cout << endl;
    // }return 0;
    cin >> N;
    endMask = (1<<N)-1;
    adjMat.resize(N, vector<int>(N,0));
    for ( int r = 0; r < N; r++ ){
        for ( int c = 0; c < N; c++ ){
            cin >> adjMat[r][c];
        }
    }

    cout << SearchPathRecursive(0, 1);

    return 0;
}