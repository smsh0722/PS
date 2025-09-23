#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct APT{
    int pos;
    int numOfStu;
};

// # of apt.
int N;
// Capacity of Bus
int K;
// Position of School
int S;

vector<APT> lAPTs;
vector<APT> rAPTs;

bool CompareAscAPT( const APT& a, const APT& b )
{
    return a.pos < b.pos;
}
bool CompareDescAPT( const APT& a, const APT& b )
{
    return a.pos > b.pos;
}

void PickupStu( APT& apt, int& busSize )
{
    int curTakeN = min( apt.numOfStu, K - busSize);
    apt.numOfStu -= curTakeN;
    busSize += curTakeN;
}

int GetMin( vector<APT>& APTs )
{
    int sum = 0;
    auto apt = APTs.begin();
    while ( apt != APTs.end() ){
        // cout << "cur apt (pos, left) \n\t"
        //     << apt->pos << ", " << apt->numOfStu << endl; // DEBUG

        int busSize = 0;
        sum += abs( S - apt->pos ) * 2;
        
        PickupStu( *apt, busSize);
        // 아파트 완료 확인
        if ( apt->numOfStu > 0 )
            continue; // 미완료라면 다음에 현재 아파트로 다시 오기

        // 돌아오며 픽업
        auto nextAPT = apt + 1;
        while ( busSize < K && nextAPT != APTs.end() ){
            // cout << "nextAPT: " << nextAPT->pos << ", " << nextAPT->numOfStu << endl;
            if ( nextAPT->numOfStu > 0 ){
                PickupStu( *nextAPT, busSize );
            }
            if ( nextAPT->numOfStu == 0 )
                nextAPT++;
        }
        apt = nextAPT;
    }

    return sum;
}

int main( void ){
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> K >> S;

    for ( int ni = 0; ni < N; ni++ ){
        int pos, stuN;
        cin >> pos >> stuN;

        if ( pos < S ){
            lAPTs.push_back({pos,stuN});
        }
        else {
            rAPTs.push_back({pos, stuN} );
        }
    }
    sort( lAPTs.begin(), lAPTs.end(), CompareAscAPT );
    sort( rAPTs.begin(), rAPTs.end(), CompareDescAPT );

    int sum = 0;
    // Greedy
        // Left
    sum += GetMin( lAPTs);
        // Right
    sum += GetMin( rAPTs);
    
    cout << sum;
    return 0;
}