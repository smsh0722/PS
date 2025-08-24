#include <iostream>
#include <vector>
#include <string>
using namespace std;

int N;

vector<int> LMemo;

char FindCharRecursive( int k, int pos )
{
    if ( k == 0 ){
        return (pos==1 ? 'm' : 'o');
    }

    // S(k-1).(k+3).S(k-1)
    char rst = 'Z';
    if ( pos <= LMemo[k-1] ){
        rst = FindCharRecursive(k-1, pos );
    }
    else if ( (pos -= LMemo[k-1]) <= (k+3) ){
        rst = pos == 1 ? 'm' : 'o';
    }
    else { // pos > (k+3)
        pos -= (k+3);
        rst = FindCharRecursive(k-1, pos );
    }

    return rst;
}

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);
    cin >> N;

    char ans = 'Z';
    LMemo.push_back(3);
    for ( int i = 0; ans == 'Z'; i++ ){
        // cout << i << "seq Length: " << LMemo[i] << endl; // DEBUG
        if ( LMemo[i] < N ){
            // Calculate LMemo[i+1]
            LMemo.push_back( LMemo[i]*2 + (i+1) + 3 );
        }
        else { // LMemo[i] >= N
            // Get answer
            ans = FindCharRecursive(i, N);
            break;
        }
    }

    cout << ans;

    return 0;
}