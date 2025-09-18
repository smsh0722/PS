#include <iostream>
#include <vector>
#include <stack>
using namespace std;

const int MAX_A = 1000000;

// Size of seq
int N;
vector<int> seq;

vector<int> numCount(MAX_A+1, 0 );

vector<int> ans;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    seq.resize(N);
    for ( int n = 0; n < N; n++ ){
        cin >> seq[n];
        numCount[seq[n]]++;
    }

    // Search Reverse using monotonic stack
    ans.resize(N, -1);
    stack<int> s;
    for ( int i = N -1; i >= 0; i-- ){
        int seqNum = seq[i];

        int localAns = -1;
        while (s.empty() == false ){
            int topNum = s.top();

            if ( numCount[seqNum] >= numCount[topNum] )
                s.pop();
            else { // numCount[seqNum] < numCount[topNum]
                localAns = topNum;
                break;
            }
        }
        s.push(seqNum);

        ans[i] = localAns;
    }

    // Ans
    for ( int i = 0; i < N; i++ ){
        cout << ans[i] << " ";
    }

    return 0;
}