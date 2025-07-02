#include <iostream>
#include <vector>
using namespace std;

const int MAX_LEGNTH = 2000;
int N, M; // N: Length of Num, M: Num of query

// r: start idx, c: length
vector<vector<bool>> bPalindromTable(MAX_LEGNTH, vector<bool>(MAX_LEGNTH+1, false));
vector<int> seqOfNum(MAX_LEGNTH);

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    // Get seq of num
    cin >> N;
    for ( int i = 0; i < N; i++ )
        cin >> seqOfNum[i];

    // Build table
    for ( int r = 0; r < N; r++ ){
        bPalindromTable[r][1] = true;
    }
    for ( int c = 2; c <= N; c++ ){
        for ( int r = 0; r < N; r++ ){
            bPalindromTable[r][c] = false;
            int si = r;
            int ei = si + c-1;
            if ( ei >= N )
                continue;
            if ( seqOfNum[si] != seqOfNum[ei] )
                continue;

            int subSi = si + 1;
            int subL = c - 2;
            if ( subL == 0 )
                bPalindromTable[r][c] = true;
            else if ( subSi < N && subL > 0 && bPalindromTable[subSi][subL] == true )
                bPalindromTable[r][c] = true;
        }
    }

    // ans for qeury
    cin >> M;
    {
        int si, ei;
        int legnth;
        for ( int queryIdx = 0; queryIdx < M; queryIdx++ ){
            cin >> si >> ei; 
            si--; ei--;
            legnth = ei - si + 1;
            cout << int(bPalindromTable[si][legnth]) << "\n"; // NOTE: endl 쓰면 출력 버퍼 지우기에 느려짐
        }
    }

    return 0;
}