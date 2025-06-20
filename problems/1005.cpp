#include <iostream>
#include <vector>

using namespace std;

/*
T: test case
N: number of building
K: number of seq
*/
int T, N, K;

int FindEffiBuildTime( int* buildTimeArr
        , vector<vector<int>>& buildSeqMat
        , int* buildEffiTimeMemo
        , int trgBuilding 
    );

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> T;
    for ( int t = 0; t < T; t++ ){
        cin >> N; cin >> K;

        int* buildTimeArr = new int[N];
        vector<vector<int>> buildSeqMat(N);
        int* buildEffiTimeMemo = new int[N];
        for ( int i = 0; i < N; i++ )
            buildEffiTimeMemo[i] = -1;

        {
            int time = 0;  
            for ( int i = 0; i < N; i++ ){
                cin >> time;
                buildTimeArr[i] = time;
            }
        }
        {
            int parent, child;
            for ( int i = 0; i < K; i++ ){
                cin >> parent >> child;
                buildSeqMat[child-1].push_back(parent-1);
            }
        }

        int targetBuilding; 
        cin >> targetBuilding;
        
        cout << FindEffiBuildTime( buildTimeArr, buildSeqMat, buildEffiTimeMemo, targetBuilding-1 ) 
            << endl;
        
        delete[] buildTimeArr;
        delete[] buildEffiTimeMemo;
    }
}   

int FindEffiBuildTime( int* buildTimeArr
        , vector<vector<int>>& buildSeqMat
        , int* buildEffiTimeMemo
        , int trgBuilding 
    )
{
    int maxTime = 0;
    int parentSize = buildSeqMat[trgBuilding].size();
    for ( int i = 0; i < parentSize; i++ ){
        int pNum = buildSeqMat[trgBuilding][i];
        if ( buildEffiTimeMemo[pNum] == -1 )
            FindEffiBuildTime( buildTimeArr, buildSeqMat, buildEffiTimeMemo, pNum );
        
        if ( maxTime < buildEffiTimeMemo[pNum] )
            maxTime = buildEffiTimeMemo[pNum];
    }

    buildEffiTimeMemo[trgBuilding] = maxTime + buildTimeArr[trgBuilding];

    return buildEffiTimeMemo[trgBuilding];
}