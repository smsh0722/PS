#include <iostream>
#include <vector>
using namespace std;

const int MAX_LEFT = 52;
const int NUM_OF_FACE = 13;
const int64_t DIVISOR = 10007;

int N; // num of picks

// [left][card face]
vector<vector<int64_t>> dpTable(MAX_LEFT+1, vector<int64_t>(NUM_OF_FACE+1, 0));

inline int64_t Combination( int64_t n, int64_t r )
{
    r = r > n - r ? n - r : r;

    int64_t rst = 1;
    vector<bool> visited( r+1, false );

    int count = r;
    while ( count > 0 ){
        count--;

        rst *= n;
        n--;
        for ( int i = 2; i <= r; i++ ){
            if ( visited[i] == true )
                continue;
            if ( rst % i == 0 ){
                rst /= i;
                visited[i] = true;
            }
        }
    }
    for ( int i = 2; i <= r; i++ ){
        if ( visited[i] == true )
            continue;
        if ( rst % i == 0 ){
            rst /= i;
            visited[i] = true;
        }
    }

    return rst;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    dpTable[0][1] = 1;
    dpTable[1][1] = 4;
    dpTable[2][1] = 6;
    dpTable[3][1] = 4;
    for ( int card = 2; card <= NUM_OF_FACE; card++ ){
        for ( int left = 0; left <= MAX_LEFT; left++ ){
            for ( int pick = 0; (pick < 4)&&(left - pick >= 0); pick++ ){
                dpTable[left][card] += Combination(4,pick)*dpTable[left-pick][card-1];
                dpTable[left][card] %= DIVISOR;
            }
        }
    }

    for ( int N = 1; N <= 52; N++ ){
        cout << "N: " << N << "= ";
        cout << "combi: " << Combination(52,N) << endl;
        cout << "table: " << dpTable[N][13] << endl;
        cout << (Combination(52,N) - dpTable[N][13])%DIVISOR << endl;
    }

    return 0;
}