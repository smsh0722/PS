#include <iostream>
#include <vector>
#include <map>
#include <algorithm>
using namespace std;

int64_t M; // Num of candy
int N; // num of people

map<int, int> candyMap; // key: hope, val: num of people
vector<int> hopeVec; // hope

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> M >> N;
    for ( int i = 0; i < N; i++ ){
        int hope;
        cin >> hope;
        if ( candyMap.find(hope) != candyMap.end() ){
            candyMap[hope]++;
        }
        else {
            candyMap[hope] = 1;
            hopeVec.push_back(hope);
        }
    }
    candyMap[0] = 0;
    hopeVec.push_back(0);

    sort( hopeVec.begin(), hopeVec.end() );
    /*
    for ( size_t i = 0; i < hopeVec.size(); i++ ){ // Debug
        int hope = hopeVec[i];
        printf("h, p: %d, %d\n", hope, candyMap[hope] );
    }*/

    for ( size_t i = hopeVec.size() - 1; i > 0 && M > 0; i-- ){
        size_t ni = i-1;
        int64_t sumDiff = (hopeVec[i] - hopeVec[ni])* int64_t(candyMap[hopeVec[i]]);
        if ( sumDiff <= M ){
            M -= sumDiff;
            candyMap[hopeVec[ni]] += candyMap[hopeVec[i]];
            candyMap.erase(hopeVec[i]);
        }
        else {
            int a = M / candyMap[hopeVec[i]];
            int b = M % candyMap[hopeVec[i]];
            int aHope = hopeVec[i] - a;
            int bHope = hopeVec[i] - a - 1;
            int numA = candyMap[hopeVec[i]] - b;
            int numB = b;
            candyMap.erase(hopeVec[i]);
            if ( candyMap.find(aHope) == candyMap.end() ){
                candyMap[aHope] = numA;
            }
            else {
                candyMap[aHope] += numA;
            }
            if ( candyMap.find(bHope) == candyMap.end() ){
                candyMap[bHope] = numB;
            }
            else {
                candyMap[bHope] += numB;
            }
            M = 0;
            break;
        }
    }

    int64_t anger = 0;
    for ( map<int,int>::iterator it = candyMap.begin(); it != candyMap.end(); it++ ){
        int64_t hope = it->first;
        int64_t num = it->second;
        // printf( "h, n: %I64d, %I64d\n", hope, num);
        anger += (hope * hope)*num; 
    }

    cout << anger;
    return 0;
}