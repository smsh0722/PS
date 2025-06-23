#include <iostream>
#include <vector>
using namespace std;

int N;

int CalculateTime( const vector<vector<int>>& parentVec
    , const vector<int>& buildTimeVec
    , vector<int>& buildSumTimeVec
    , int trg );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);
    cin >> N;

    vector<int> buildTimeVec(N);
    vector<vector<int>> parentVec(N);
    vector<int> buildSumTimeVec(N, -1);
    for ( int i = 0; i < N; i++ ){
        int input;
        cin >> input;
        
        buildTimeVec[i] = input;

        // Building number
        cin >> input;
        while ( input != -1 ){
            parentVec[i].push_back(input-1);
            cin >> input;
        }
        
        if ( parentVec[i].size() == 0 )
            buildSumTimeVec[i] = buildTimeVec[i];
    }

    for ( int i = 0; i < N; i++ ){
        cout << CalculateTime(parentVec, buildTimeVec, buildSumTimeVec, i ) << endl;
    }
}

int CalculateTime( const vector<vector<int>>& parentVec
    , const vector<int>& buildTimeVec
    , vector<int>& buildSumTimeVec
    , int trg )
{
    if ( buildSumTimeVec[trg] != -1 )   
        return buildSumTimeVec[trg];

    int maxTime = 0;
    for ( int i = 0; i < parentVec[trg].size(); i++ ){
        int p = parentVec[trg][i];
        int time = CalculateTime(parentVec, buildTimeVec, buildSumTimeVec, p );
        if ( maxTime < time )
            maxTime = time;
    }

    buildSumTimeVec[trg] = maxTime + buildTimeVec[trg];
    return buildSumTimeVec[trg];
}