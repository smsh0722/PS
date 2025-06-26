#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;

struct TimeData{
    int s, e; // s: start, e: end
};

bool compare( TimeData a, TimeData b);

int main ( void ) 
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> N;
    vector<TimeData> meetingVec;
    {
        int s, e;
        for ( int i = 0;  i< N; i++ ){
            cin >> s >> e;
            meetingVec.push_back(TimeData{s, e} );
        }
    }

    sort(meetingVec.begin(), meetingVec.end(), compare);

    /*
    for ( int i = 0; i < N; i++ ){ // Debug
        TimeData m = meetingVec[i];
        cout << m.s << " " << m.e << endl;
    }*/

    int meetingCount = 0;
    {
        int cur_e = 0;
        for ( int i = 0; i < N; i++ ){
            if ( cur_e <= meetingVec[i].s ){
                cur_e = meetingVec[i].e;
                meetingCount++;
            }
        }
    }
    
    cout << meetingCount << endl;
    return 0;
}
bool compare( TimeData a, TimeData b)
{
    if ( a.e == b.e )
        return a.s < b.s; // asc //NOTE: (3,3) 같은 경우 회의 가능하려면 s도 asc로
    return a.e < b.e; // asc
}