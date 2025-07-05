#include <iostream>
#include <vector>

using namespace std;

struct Ad{
    int cost;
    int numOfGet;
};

const int MAX_INT = ~(1<<31);

int C, N;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    
    cin >> C >> N;

    vector<Ad> ads(N);
    {
        int cost, numOfGet;
        for ( int i = 0; i < N; i++ ){
            cin >> cost >> numOfGet;
            ads[i] = Ad{cost, numOfGet};
        }
    }

    vector<int> table(C+1,MAX_INT);
    table[0] = 0;
    for ( int c = 1; c <=C; c++ ){
        int minCost = MAX_INT;
        for ( int adsIdx = 0; adsIdx < N; adsIdx++){
            int newCost = MAX_INT;

            Ad ad = ads[adsIdx];
            int remain = c - ad.numOfGet;
            if ( remain < 0 )
                newCost = ad.cost;
            else {
                newCost = table[remain] + ad.cost;
            }

            if ( minCost > newCost )
                minCost = newCost;
        }
        table[c] = minCost;
    }

    cout << table[C];
}