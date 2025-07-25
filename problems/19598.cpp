/* NOTE:
다른 풀이)
빨리 시작하는 회의부터 순회한다.
진행 중인 회의는 끝나는 시간을 기준으로 하는 q를 통해 최대 동시진행 회의 수를 구할 수 있다.
*/
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

struct Meeting{
    int st;
    int et;
};

const int MAX_N = 100000;
int N;

vector<int> compressedTime;
vector<Meeting> meetings(MAX_N);
vector<int> prefixSum(MAX_N*2, 0);

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    for ( int n = 0; n < N; n++ ){
        cin >> meetings[n].st >> meetings[n].et;
        compressedTime.push_back(meetings[n].st);
        compressedTime.push_back(meetings[n].et);
    }

    sort( compressedTime.begin(), compressedTime.end() );

    compressedTime.erase( unique(compressedTime.begin(), compressedTime.end() ), compressedTime.end() );

    for ( size_t i = 0; i < compressedTime.size(); i++ ){ // Debug
        cout << compressedTime[i] << " ";
    }

    for ( size_t i = 0; i < meetings.size(); i++ ){
        Meeting m = meetings[i];
        int l = lower_bound( compressedTime.begin(), compressedTime.end(), m.st ) - compressedTime.begin();
        int r = lower_bound( compressedTime.begin(), compressedTime.end(), m.et) - compressedTime.begin();

        prefixSum[l] += 1;
        prefixSum[r] -= 1;
    }

    int max = prefixSum[0];
    for ( size_t i = 1; i < prefixSum.size(); i++ ){
        prefixSum[i] += prefixSum[i-1];
        max = max < prefixSum[i] ? prefixSum[i] : max;
    }

    cout << max;

    return 0;
}