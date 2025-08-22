#include <iostream>
#include <vector>
#include <queue>
using namespace std;

const int MAX_POS = 200000;
const int MAX_INT = ~(1<<31);

/*
1-2-4-8-7
1-2-3-6-7
*/
struct Memo {
    int depth;
    vector<int> parents;
    Memo() { depth = MAX_INT; }
};

struct QueueData{
    int pos;
    int depth;
};

vector<Memo> memo( MAX_POS+1, Memo() );
queue<QueueData> bfsQ;

// Starting Position
int N;
// Destination Position
int K;

int64_t CalculateNumOfCasesRecursive( const int cur )
{
    int64_t rst = 0;
    for ( auto p : memo[cur].parents ){
        if ( p == cur ){
            rst = 1;
            break;
        }
        // cout << "In node " << cur << endl; // Debug
        // cout << "DFS to " << p << endl; // Debug
        rst += CalculateNumOfCasesRecursive( p );
    }

    return rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N >> K;

    memo[N].depth = 0;
    memo[N].parents.push_back(N);
    bfsQ.push( {N, 0});
    while ( bfsQ.empty() == false ){
        QueueData cur = bfsQ.front();
        bfsQ.pop();

        vector<QueueData> adjList;
        adjList.push_back( {cur.pos+1, cur.depth+1});
        adjList.push_back( {cur.pos-1, cur.depth+1});
        adjList.push_back( {cur.pos*2, cur.depth+1});
        for ( size_t i = 0; i < adjList.size(); i++ ){
            QueueData dst = adjList[i];
            if ( dst.pos < 0 || dst.pos > MAX_POS )
                continue;
            
            if ( memo[dst.pos].depth < dst.depth )
                continue;
            
            if ( memo[dst.pos].depth == MAX_INT ){
                memo[dst.pos].depth = dst.depth;
                bfsQ.push( dst );
            }
            memo[dst.pos].parents.push_back(cur.pos);
        }
    }

    // for ( size_t i = 0; i <= K*2; i++ ){ // Debug
    //     printf("%d'th depth = %d\n ", i, memo[i].depth );
    //     printf( "parents: ");
    //     for ( size_t j = 0; j < memo[i].parents.size(); j++ ){
    //         cout << memo[i].parents[j] << " ";
    //     }
    //     cout << endl;
    // }

    cout << memo[K].depth << endl;
    cout << CalculateNumOfCasesRecursive(K);

    return 0;
}