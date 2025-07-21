#include <iostream>
#include <vector>
using namespace std;

struct Strahler{
    vector<int> strahler;
    vector<vector<int>> adjList; // adjList[dst] = src
};

const int MAX_NODE_NUM = 1000;

int T; // num of test
int K; // idx of test
int M; // num of nodes, range[1,M]
int P; // num of edges

int CalculateStrahler( Strahler& s, int node )
{
    if ( s.strahler[node] > 0 )
        return s.strahler[node];
    
    int max = 0;
    bool bDup = false;
    for ( size_t i = 0; i < s.adjList[node].size(); i++ ){
        int tmp = CalculateStrahler(s, s.adjList[node][i] );
        if( max < tmp ){
            max = tmp;
            bDup = false;
        }
        else if ( max == tmp ){
            bDup = true;
        }
    }

    if ( max == 0 )
        s.strahler[node] = 1;
    else if ( bDup == true )
        s.strahler[node] = max + 1;
    else 
        s.strahler[node] = max;

    return s.strahler[node];
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> T;
    for ( int t = 0; t < T; t++ ){
        cin >> K >> M >> P;

        Strahler s;
        s.strahler.resize(M+1, 0);
        s.adjList.resize(M+1);
        for ( int i = 0; i < P; i++ ){
            int src, dst;
            cin >> src >> dst;
            s.adjList[dst].push_back(src);
        }
        
        printf( "%d %d\n", K, CalculateStrahler(s, M) );
    }

    return 0;
}