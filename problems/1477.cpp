#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_INT = ~(1<<31);
int N; // num of cur building
int M; // num of new building
int L; // num of Length

vector<int> buildings;
vector<int> distList;
vector<vector<int>> table; // [new buildings num(0~M)][dist Idx(0~N)]

inline int DivideBalance( int val, int divisor )
{  
    int q = val / divisor;
    if ( val % divisor != 0 )
        q++;
    return q;
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M >> L;

    buildings.resize(N);
    for ( int i = 0; i < N; i++ ){
        cin >> buildings[i];
    }
    sort( buildings.begin(), buildings.end() );

    distList.resize(N+1,0);
    {
        int left = 0;
        for ( int i = 0; i < N; i++ ){
            distList[i] = buildings[i] - left;
            left = buildings[i];
        }
        distList[N] = L - left;
    }

    table.resize(M+1, vector<int>(N+1, 0) );
    // Init
    for ( int nOfNewB = 0; nOfNewB <= M; nOfNewB++ ){
        table[nOfNewB][0] = DivideBalance( distList[0], nOfNewB+1 );
    }
    // Build the others
    for( int distIdx = 1; distIdx <= N; distIdx++ ){
        for ( int curNumOfNewB = 0; curNumOfNewB <= M; curNumOfNewB++ ){
            int rst = MAX_INT;
            for ( int prevNumOfNewB = 0; prevNumOfNewB <= curNumOfNewB; prevNumOfNewB++ ){
                int tmpMax = max( table[prevNumOfNewB][distIdx-1], DivideBalance(distList[distIdx], curNumOfNewB-prevNumOfNewB+1) );
                rst = rst > tmpMax ? tmpMax : rst;
            }
            table[curNumOfNewB][distIdx] = rst;
        }
    }

    cout << table[M][N];

    return 0;
}