#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>
using namespace std;

struct Bus{
    int num;
    int a, b;
};
struct CompareBusAscByA{
    bool operator()( const Bus& x, const Bus& y )
    {
        if ( x.a == y.a )
            return x.b < y.b;
        return x.a > y.a;
    }
};

const int MAX_STATION_NUM = 1000000000;
const int MIN_STATION_NUM = -MAX_STATION_NUM;

// # of stations
int N;
// # of buses
int M;

priority_queue<Bus, vector<Bus>, CompareBusAscByA> buses;
priority_queue<Bus, vector<Bus> > answerBuses;

vector<int> answers;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    for ( int mi = 1; mi <= M; mi++ ){
        int a, b;
        cin >> a >> b;
        if ( a > b ){
            a = (a - N);
        }
        buses.push({mi, a, b});
    }

    int curNum = MIN_STATION_NUM;
    int minNum = MAX_STATION_NUM;
    while ( buses.empty() == false ){
        Bus cur = buses.top();
        buses.pop();

        // printf("bus: num\ta\tb\n");
        // printf("     %d\t\t%d\t%d\n", cur.num, cur.a, cur.b );

        if ( cur.b <= curNum || (N+minNum) <= cur.a)
            continue;
        
        curNum = cur.b;
        minNum = min( minNum, cur.a);
        // cout << "new curNum: " << curNum << endl;

        answers.push_back(cur.num);
    }

    sort( answers.begin(), answers.end() );
    for ( auto b: answers ){
        cout << b << " ";
    };

    return 0;
}