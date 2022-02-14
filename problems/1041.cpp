#include <iostream>
#include <vector>

using namespace std;

bool adjCheck( const vector<bool>& visited, const vector< vector<int> >& adjList )
{
    vector<int> trgV;
    {
        for ( int i = 0; i < 6; i++ ){
            if ( visited[i] == true ){
                trgV.push_back(i);
            }
        }
    }

    const int TRG_SIZE = trgV.size();
    for( int i = 0; i < TRG_SIZE; i++ ){
        const int trg = trgV[i];
        for ( int j = 0; j < TRG_SIZE; j++ ){
            if ( i != j ){
                int vFlag = false;
                {
                    const vector<int>& trgList = adjList[trg];
                    for ( int k = 0; k < trgList.size(); k++ ){
                        if ( trgList[k] == trgV[j] ){
                            vFlag = true;
                        }
                    }
                }
                if ( vFlag == false ){
                    return false;
                }
            }
        }
    }
    return true;
}

int64_t DFS( const int src, const int dice[6], const vector< vector<int> >& adjList, const int goalLevel, int level, vector<bool> visited )
{
    visited[src] = true;
    if ( level > 2 && adjCheck(visited, adjList ) == false ){
        return (50 * 60 + 1);
    }

    int64_t sum = dice[src];
    int64_t min = 0;
    vector<bool> save = visited;
    if ( level < goalLevel ){
        min = 50 * 6 + 1;
        level++;
        for ( int i = 0; i < 4; i++ ){
            int dst = adjList[src][i];
            if ( visited[dst] == true ){
                continue;
            }
            else {
                int tmp = DFS( dst, dice, adjList, goalLevel, level, visited );
                min = min > tmp ? tmp : min;
            }
            visited = save;
        }
    }
    return sum + min;
}

int main( void )
{
    const vector<vector<int>> adjList = {
        { 1, 2, 3, 4 },
        { 0, 2, 3, 5 },
        { 0, 1, 4, 5 },
        { 0, 1, 4, 5 },
        { 0, 2, 3, 5 },
        { 1, 2, 3, 4 },
    };

    int64_t N;
    cin >> N;

    const int DICESIZE = 6;
    int dice[DICESIZE];
    {
        for ( int i = 0; i < DICESIZE; i++ ){
            cin >> dice[i];
        }
    }

    if ( N == 1 ){
        int64_t max = 0;
        int64_t sum = 0;
        for ( int i = 0; i < DICESIZE; i++ ){
            sum += dice[i];
            max = max < dice[i] ? dice[i] : max;
        }
        sum -= max;

        cout << sum;
        return 0;
    }

    int64_t sum1;
    {
        int64_t min = 50 * 1 + 1;
        for ( int i = 0; i < DICESIZE; i++ ){
            min = min > dice[i] ? dice[i] : min;
        }
        sum1 = min * ( (N-2)*(N-2)*5 + (N-2)*4);
    }

    int64_t sum2;
    {
        int64_t min = 50 * 2 + 1;
        for ( int i = 0; i < DICESIZE; i++ ){
            vector<bool> visited = vector<bool>(6, false );
            int64_t sum = DFS( i, dice, adjList, 2, 1, visited );
            min = min > sum ? sum : min;
        }
        sum2 = min * ( 4 * 2 * ( N - 2 ) + 4 );
    }

    int64_t sum3;
    {
        int64_t min = 50 * 3 + 1;
        for ( int i = 0; i < DICESIZE; i++ ){
            vector<bool> visited = vector<bool>(6, false );
            int64_t sum = DFS( i, dice, adjList, 3, 1, visited );
            min = min > sum ? sum : min;
        }
        sum3 = min * 4;
    }

    cout << sum1 + sum2 + sum3;
    
    return 0;
}