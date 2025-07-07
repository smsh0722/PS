#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct NumOfPower{
    int64_t num;
    int64_t pOf3;
    int64_t pOf2;
};

const int MAX_N = 100;
int N;

vector<NumOfPower> seq(MAX_N);

inline void CalNumOfPower( NumOfPower& numOfPower)
{
    int64_t num = numOfPower.num;
    while ( num % 2 == 0 ){
        num /= 2;
        numOfPower.pOf2++;
    }
    while ( num % 3 == 0 ){
        num /= 3;
        numOfPower.pOf3++;
    }
}

bool MyComp( NumOfPower& a, NumOfPower& b )
{
    if ( a.pOf3 > b.pOf3 )
        return true;
    else if ( a.pOf3 == b.pOf3 ){
        return a.pOf2 < b.pOf2;
    }
    else {
        return false;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    {
        int64_t num;
        for ( int i = 0; i < N; i++ ){
            cin >> num;
            NumOfPower numOfPower = NumOfPower{num, 0, 0};
            CalNumOfPower( numOfPower );
            seq[i] = numOfPower;
        }
    }

    sort( seq.begin(), seq.begin() + N, MyComp );

    for ( int i = 0; i < N; i++ ){
        cout << seq[i].num << " ";
    }

    return 0;
}