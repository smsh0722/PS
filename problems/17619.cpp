#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

struct Log{
    int xl, xr;
    int logNum;
    int64_t y;
};

// Num of Log
int N;
// Num of Query
int Q;

vector<Log> logs;
vector<int> logGroups;

bool CompareLog( const Log& a, const Log& b )
{
    if ( a.xl == b.xl ){
        return a.xr < b.xr;
    }
    else {
        return a.xl < b.xl;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> Q;

    logs.resize(N);
    logGroups.resize(N+1, -1);
    for ( int i = 0; i < N; i++ ){
        cin >> logs[i].xl >> logs[i].xr >> logs[i].y;
        logs[i].logNum = i + 1;
    }
    sort( logs.begin(), logs.end(), CompareLog );

    // Grouping
    {
        int groupXR = -1;
        int groupNum = 0;
        for ( int i = 0; i < N; i++ ){
            Log curLog = logs[i];
            // printf( "xl: %d, xr: %d, y: %d = log %d\n", curLog.xl, curLog.xr, curLog.y, curLog.logNum);
            if ( groupXR < curLog.xl ){ // new Group
                // printf("case 1\n");
                groupNum++;
            }
            groupXR = groupXR > curLog.xr ? groupXR : curLog.xr;
            logGroups[curLog.logNum] = groupNum;
        }
    }

    // for ( int i = 1; i <= N; i++ ){// DEBUG
    //     printf("log[%d]'s group num: %d\n", i, logGroups[i]); 
    // }

    // Answer each query
    for ( int q = 0; q < Q; q++ ){
        int la, lb;
        cin >> la >> lb;
        int ga = logGroups[la];
        int gb = logGroups[lb];
        if ( ga == gb )
            cout << "1\n";
        else 
            cout << "0\n";
    }

    return 0;
}