/* SOL) BFS
*/
#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Bottles{
    int bottle[3] = {0};
};

const int MAX_CAPACITY = 200;

// Capacity of A, B, C
Bottles capacityOf;

// visited[A][B][C] = false or true
bool visited[MAX_CAPACITY+1][MAX_CAPACITY+1][MAX_CAPACITY+1] = {false};

bool bPossibleCases[MAX_CAPACITY+1] = {false};

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> capacityOf.bottle[0] >> capacityOf.bottle[1] >> capacityOf.bottle[2];

    queue<Bottles> q;
    q.push({0,0, capacityOf.bottle[2]});
    visited[0][0][capacityOf.bottle[2]] = true;
    while ( q.empty() == false ){
        Bottles f = q.front();
        q.pop();

        for ( int src = 0; src < 3; src++ ){
            for ( int dst = 0; dst < 3; dst++ ){
                if ( src == dst ) 
                    continue;
                
                int moveSize = min( capacityOf.bottle[dst] - f.bottle[dst], f.bottle[src] );
                Bottles nextBottles = f;
                nextBottles.bottle[src] -= moveSize;
                nextBottles.bottle[dst] += moveSize;
                if ( visited[nextBottles.bottle[0]][nextBottles.bottle[1]][nextBottles.bottle[2]] == false ){
                    q.push(nextBottles);
                    visited[nextBottles.bottle[0]][nextBottles.bottle[1]][nextBottles.bottle[2]] = true;

                    if ( nextBottles.bottle[0] == 0 )
                        bPossibleCases[nextBottles.bottle[2]] = true;
                }
            }
        }
    }

    bPossibleCases[capacityOf.bottle[2]] = true;
    for ( int i = 0; i <= MAX_CAPACITY; i++ ){
        if ( bPossibleCases[i] == true )
            cout << i << " ";
    }

    return 0;
}