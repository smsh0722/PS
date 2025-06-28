/* NOTE:
처음엔 dp로 보였다.
그러나 쪼개지는 경우의 수가 너무 많아 의미가 없다.
시험장에서도 dp가 떠오르더라도 가능 여부를 스스로 판단할 수 있어야겠다.
*/
#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N, K; // N: num of kids, K: num of set
int W; // k: num of wall

struct DiffData{
    int lPos;
    int Diff;
};

bool DiffDesc(const DiffData& a, const DiffData& b )
{
    return a.Diff > b.Diff;
};
bool WallAsc( const int a, const int b )
{
    return a < b;
};

vector<int> heights;
vector<DiffData> hDiff;
vector<int> wPos;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    
    cin >> N >> K;
    W = K - 1;
    {
        int prev;
        int cur ;
        
        cin >> prev;
        heights.push_back(prev);
        for ( int i = 1; i < N; i++ ){
            cin >> cur;
            heights.push_back(cur);

            hDiff.push_back(DiffData{i-1, cur-prev});
            prev = cur;
        }
    }
    sort(hDiff.begin(), hDiff.end(), DiffDesc); 
    
    for ( int i = 0; i < W; i++ ){
        int newWallPos = hDiff[i].lPos;
        wPos.push_back(newWallPos);
    }
    sort ( wPos.begin(), wPos.end(), WallAsc );

    int64_t cost = 0;
    int lIdx = 0;
    for ( int w = 0; w < W; w++ ){
        int rIdx = wPos[w];
        cost += heights[rIdx] - heights[lIdx];
        lIdx = rIdx+1;
    }
    cost += heights[N-1] - heights[lIdx];

    cout << cost;

    return 0;
}