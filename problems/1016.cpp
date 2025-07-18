#include <iostream>
#include <vector>
#include <algorithm>
#include <cmath>
using namespace std;

const int64_t MAX_TRGMAX = 1000000000000+1000000;

int64_t trgMin, trgMax;

vector<int64_t> squareNumArr;
vector<bool> bPrimeArr;
vector<bool> noSqaure;

int main (void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> trgMin >> trgMax;

    int64_t sqrtMax = ceil(sqrt(MAX_TRGMAX));
    bPrimeArr.resize(sqrtMax+1, true);
    for( int64_t i = 2; i <= sqrtMax; i++ ){
        if ( bPrimeArr[i] == false )
            continue;
        // build square num
        squareNumArr.push_back(i*i);

        // Build Prime num;
        for ( int64_t j = 2; i*j <= sqrtMax; j++ ){
            bPrimeArr[i*j] = false;
        }
    }
/*
    for ( int i = 0; i < 168; i++ ){
        cout << squareNumArr[i] << endl;
    }
    cout << "here\n";
*/
    //printf( "size: %d", squareNumArr.size() );

    int64_t count = trgMax - trgMin + 1;
    noSqaure.resize(count, true );
    for ( size_t pi = 0; pi < squareNumArr.size(); pi++ ){
        int64_t i = trgMin % squareNumArr[pi] == 0 ?
                0 : trgMin - (trgMin % squareNumArr[pi]) + squareNumArr[pi] - trgMin;
        while ( i < count ){
            noSqaure[i] = false;
            i += squareNumArr[pi];
        }
    }

    for ( size_t i = 0; i < noSqaure.size(); i++ ){
        count -= int64_t(noSqaure[i] == false);
    }

    cout << count;

    return 0;
}