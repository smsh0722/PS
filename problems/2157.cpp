#include <iostream>
#include <vector>
using namespace std;

struct Airway{
    int dst;
    int grade;
};

int N; // num of city
int M; // max travel num
int K; // num of airway

vector<vector<Airway>> airList;// [src][airway idx]
vector<vector<int>> memo; // [remain][city idx]

int GetMaxRouteRecursive( int cityIdx, int remainNum )
{
    if ( cityIdx == N )
        return 0;
    if ( remainNum == 0 && cityIdx != N)
        return -1;
    if ( memo[remainNum][cityIdx] != -1 )
        return memo[remainNum][cityIdx];

    int max = -1;
    for ( size_t airIdx = 0; airIdx < airList[cityIdx].size(); airIdx++ ){
        Airway w = airList[cityIdx][airIdx];
        int tmpRst = GetMaxRouteRecursive( w.dst, remainNum - 1);
        if ( tmpRst == -1 )
            continue;
        tmpRst += w.grade;
        max = max < tmpRst ? tmpRst : max;
    }

    memo[remainNum][cityIdx] = max;
    return max;
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> K;
    airList.resize(N+1);
    memo.resize(M+1, vector<int>(N+1, -1));
    {
        int a, b, c;
        for ( int i = 0; i < K; i++ ){
            cin >> a >> b >> c;
            if ( a > b )
                continue;
            airList[a].push_back(Airway{b, c});
        }
    }

    cout << GetMaxRouteRecursive(1, M-1 );

    return 0;
}