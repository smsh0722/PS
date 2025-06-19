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
        , vector<int>* buildSeqMat
        , int* buildSeqMemo
        , int trgBuilding 
    );

int main ( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> T;
    for ( int t = 0; t < T; t++ ){
        cin >> N; cin >> K;

        int* buildTimeArr = new int[N];
        vector<int>* buildSeqMat = new vector<int>[N];
        int* buildSeqMemo = new int[N];
        for ( int i = 0; i < N; i++ )
            buildSeqMemo[i] = -1;

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
                parent--; child--;
                buildSeqMat[child].push_back(parent);
            }
        }
        int targetBuilding = -1;
        cin >> targetBuilding;
        
        cout << FindEffiBuildTime( buildTimeArr, buildSeqMat, buildSeqMemo, targetBuilding-1 ) 
            << endl;
        
        delete[] buildTimeArr;
        delete[] buildSeqMemo;
        delete[] buildSeqMat;
    }
}   

int FindEffiBuildTime( int* buildTimeArr
        , vector<int>* buildSeqMat
        , int* buildSeqMemo
        , int trgBuilding 
    )
{
    int parent_size = buildSeqMat[trgBuilding].size();
    int max_time = 0;

    for ( int i = 0; i < parent_size; i++ ){
        int pNum = buildSeqMat[trgBuilding][i];
        if (buildSeqMemo[pNum] == -1)
            FindEffiBuildTime( buildTimeArr, buildSeqMat, buildSeqMemo, pNum );
        
        if ( max_time < buildSeqMemo[pNum] )
            max_time = buildSeqMemo[pNum];
    }

    buildSeqMemo[trgBuilding] = max_time + buildTimeArr[trgBuilding];

    return buildSeqMemo[trgBuilding];
}