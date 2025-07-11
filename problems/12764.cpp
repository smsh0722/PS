#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

struct OccupyData{
    int endTime;
    int pcIdx;
};

struct OccupyCompare{
    bool operator()(const OccupyData& a, const OccupyData& b ) 
    {
        return a.endTime > b.endTime; // 오름차순
    }
};

struct PcListCompare{
    bool operator()(const int a, const int b )
    {
        return a > b; // 오름차순
    }
};

struct TimeData{
    int s, e;

};

int N;
vector<TimeData> users;
vector<int> pcUseCount;
priority_queue<OccupyData, vector<OccupyData>, OccupyCompare> occupied;
priority_queue<int, vector<int>, PcListCompare> pcList;
int maxComputer = 0;

bool TimeCompare( const TimeData& a, const TimeData& b )
{
    return a.s < b.s;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    users.resize(N);
    for ( int i = 0; i < N; i++ ){
        int s, e;
        cin >> s >> e;
        users[i] = TimeData{s, e};
    }

    sort( users.begin(), users.end(), TimeCompare );

    int countCurrentOccupied = 0;
    for ( int u = 0; u < N; u++ ){
        TimeData ut = users[u];
        // Pop Occupied PC
        while ( occupied.empty() == false ){
            OccupyData pc = occupied.top();
            if ( pc.endTime <= ut.s ){
                occupied.pop();
                countCurrentOccupied--;
                pcList.push( pc.pcIdx );
            }
            else {
                break;
            }
        }

        //printf( "user: %d\n", u );

        // Use PC
        int pcIdx = -1;
        if ( pcList.empty() == true ){
            pcIdx = countCurrentOccupied;
            pcUseCount.push_back(1);
            maxComputer = countCurrentOccupied;
          //  printf("new pc! %d\n", pcIdx);
        }
        else {
            pcIdx = pcList.top();
            pcList.pop();
            pcUseCount[pcIdx]++;
            //printf("least pc! %d\n", pcIdx);
        }
        countCurrentOccupied++;
        maxComputer = maxComputer < countCurrentOccupied ? countCurrentOccupied : maxComputer;
        occupied.push( OccupyData{ut.e, pcIdx} );
    }

    cout << maxComputer << "\n";
    for ( size_t i = 0; i < pcUseCount.size(); i++ )
        cout << pcUseCount[i] << " ";

    return 0;
}