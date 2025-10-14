/* SOL) DFS
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_CAPACITY = 200;

// Capacity of A, B, C
int capacityOf[3] = {0};

// visited[A][B][C] = false or true
bool visited[MAX_CAPACITY+1][MAX_CAPACITY+1][MAX_CAPACITY+1] = {false};

bool bPossibleCases[MAX_CAPACITY+1] = {false};

void SearchNextCasesRecursive( vector<int>& bottles )
{
    for ( int src = 0; src < 3; src++ ){
        for ( int dst = 0; dst < 3; dst++ ){
            if ( src == dst ) 
                continue;
            
            int moveSize = min( capacityOf[dst] - bottles[dst], bottles[src] );
            bottles[src] -= moveSize;
            bottles[dst] += moveSize;
            if ( visited[bottles[0]][bottles[1]][bottles[2]] == false ){
                visited[bottles[0]][bottles[1]][bottles[2]] = true;

                if ( bottles[0] == 0 )
                    bPossibleCases[bottles[2]] = true;
                SearchNextCasesRecursive( bottles );
            }
            bottles[src] += moveSize;
            bottles[dst] -= moveSize;
        }
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> capacityOf[0] >> capacityOf[1] >> capacityOf[2];

    vector<int> bottles(3);
    bottles = {0,0,capacityOf[2]};
    visited[0][0][capacityOf[2]] = true;
    SearchNextCasesRecursive( bottles );

    bPossibleCases[capacityOf[2]] = true;
    for ( int i = 0; i <= MAX_CAPACITY; i++ ){
        if ( bPossibleCases[i] == true )
            cout << i << " ";
    }

    return 0;
}