#include <iostream>
#include <vector>

using namespace std;

struct Ads{
    int cost;
    int numOfGet;
};

const int MAX_INT = ~(1<<31);

int C, N; // C: Number of customer, N: Number of ads

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> C >> N;

    vector<Ads> ads(N);
    { // Inupt Ads
        int cost, numOfGet;
        for ( int n = 0; n < N; n++ ){
            cin >> cost >> numOfGet;
            ads[n] = Ads{cost, numOfGet};
        }
    }

    /*
            ads0 ads1 ads2.. N-1
        0
        1
        .
        .
        C
    */
    vector<vector<int>> table(C+1, vector<int>(N, MAX_INT) );
    {
        for ( int c = 0; c < N; c++ )
            table[0][c] = 0;
        for ( int r = 1; r <= C; r++ ){
            int count = r / ads[0].numOfGet;
            if ( r % ads[0].numOfGet != 0 )
                count++;
            table[r][0] = ads[0].cost*count;
        }
        for ( int c = 1 ; c < N; c++ ){
            for ( int r = 1; r <= C; r++ ){
                int minCost = MAX_INT;
                for ( int i = 0; true ; i++ ){
                    int cost = ads[c].cost * i;
                    int numOfGet = ads[c].numOfGet * i;
                    int remain = (r - numOfGet) >= 0 ? r - numOfGet : 0;
                    int newCost = MAX_INT;
                    if ( table[remain][c-1] != MAX_INT ){
                        newCost = table[remain][c-1] + cost;
                    }
                    if ( minCost > newCost )
                        minCost = newCost;

                    if ( numOfGet >= r )
                        break;
                }
                table[r][c] = minCost;
            }
        }
    }
    /*
    for ( int r = 0; r <= C; r++ ){
        cout << "r: " << r << " = " ;
        for ( int c = 0; c < N; c++ ){
            cout << table[r][c] << " ";
        } cout << endl;
    }*/
    cout << table[C][N-1] << endl;
}