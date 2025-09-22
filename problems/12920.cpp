#include <iostream>
#include <vector>
using namespace std;

struct ObjectData{
    int w;
    int value;
};

// Num of obejct types
int N;
// Weight limit of Knapsack
int M;

vector<ObjectData> objects;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    
    objects.push_back({0,0});
    for ( int ni = 0; ni < N; ni++ ){
        // weight
        int V;
        // value
        int C;
        // num
        int K;

        cin >> V >> C >> K;
        int curK = K;
        while ( curK > 0){
            int nextK = curK / 2;
            objects.push_back({V*(curK-nextK), C*(curK-nextK)});
            curK = nextK;
        }
    }

    vector<vector<int>> dpTable( M+1, vector<int>(objects.size(), 0) );
    for ( int m = 1; m <= M; m++ ){
        for ( size_t objI = 1; objI < objects.size(); objI++ ){
            ObjectData obj = objects[objI];

            // 현재 item 포함x 가치 vs 현재 아이템 포함o 가치
            dpTable[m][objI] = dpTable[m][objI-1];
            if( m - obj.w >= 0 ){
                dpTable[m][objI] = max( dpTable[m][objI], dpTable[m-obj.w][objI-1] + obj.value );
            }
        }
    }

    cout << dpTable[M][objects.size()-1];

    return 0;
}