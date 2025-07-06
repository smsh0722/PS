#include <iostream>
#include <vector>

using namespace std;

const int MAX_N = 123456;

int N; // num of island: 1~MAX_N

vector<vector<int>> adjList(MAX_N+1); // [1, MAX_N];
vector<int64_t> islands(MAX_N+1);

int64_t CalMaxSheepRecursive( int src );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    {
        char animal;
        int64_t num;
        int dst;
        for ( int src = 2; src <= N; src++ ){
            cin >> animal >> num >> dst;
            if( animal == 'W' )
                num = -num;
            islands[src] = num;
            adjList[dst].push_back(src);
        }
    }

    cout << CalMaxSheepRecursive(1);

    return 0;
}

int64_t CalMaxSheepRecursive( int src )
{
    int64_t rst = islands[src];

    for ( size_t i = 0; i < adjList[src].size(); i++ ){
        int dst = adjList[src][i];
        rst += CalMaxSheepRecursive(dst);
    }

    if ( rst < 0 )
        return 0;
    else 
        return rst;
}