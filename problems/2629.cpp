#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

const int MAX_BALL = 7;
const int MAX_BOX = 30;
const int MAX_WEIGHT = 15000;

int numOfBox;
int numOfBall;

// row: abs(weight[0~40,000]), column: box Idx
vector<vector<bool>> table(MAX_WEIGHT+1, vector<bool>(MAX_BOX, false ) );
vector<int> boxes(MAX_BOX);
vector<int> balls(MAX_BALL);

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> numOfBox;
    for( int i = 0; i < numOfBox; i++ )
        cin >> boxes[i];
    cin >> numOfBall;
    for ( int i = 0; i < numOfBall; i++)
        cin >> balls[i];
    
    // Build table
    table[boxes[0]][0] = true;
    for ( int i = 0; i < numOfBox; i++ )
        table[0][i] = true;
    for ( int b = 1; b < numOfBox; b++ ){
        for ( int w = 0; w <= MAX_WEIGHT; w++ ){
            int prevW = abs(w - boxes[b]);
            int prevB = b - 1;
            if ( prevW <= MAX_WEIGHT && table[prevW][prevB] == true ){
                table[w][b] = true;
                continue;
            }
            prevW = abs( w + boxes[b] );
            if( prevW <= MAX_WEIGHT && table[prevW][prevB] == true ){
                table[w][b] = true;
                continue;
            }
            prevW = w;
            if ( table[prevW][prevB] == true ){
                table[w][b] = true;
                continue;
            }
        }
    }

    vector<bool> flags(numOfBall, false);
    for ( int j = 0; j < numOfBall; j++ ){
        int ballW = balls[j];
        if ( ballW > MAX_WEIGHT )
            continue;
        if( table[ballW][numOfBox-1] == true )
            flags[j] = true;
    }

    // print ans
    for ( int i = 0; i < numOfBall; i++ ){
        if ( flags[i] == true )
            cout << "Y";
        else 
            cout << "N";
        cout << " ";
    }

    return 0;
}