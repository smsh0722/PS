#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

const int MAX_INT = ~(1<<31);

// num of devices
int N;
// num of concent
int M;

vector<int> devices;
vector<int> concents;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N >> M;
    devices.resize(N);
    concents.resize(M, 0);
    for ( int i = 0; i < N; i++ ){
        cin >> devices[i];
    }

    sort(devices.begin(), devices.end() );
    
    int time = 0;
    int di = N-1;
    while ( true ){
        // add device
        for ( int i = 0; i < M && di >= 0; i++ ){
            if ( concents[i] == 0 ){
                concents[i] = devices[di--];
            }
        }

        /*
        1) Find Min Time
        2) Remove Min Time
        */
        int minTime = MAX_INT;
        for ( int i = 0 ; i < M; i++ ){
            if ( concents[i] == 0 )
                continue;
            minTime = minTime > concents[i] ? concents[i] : minTime;
        }

        if ( minTime == MAX_INT )
            break;

        time += minTime;
        for ( int i = 0; i < M; i++ ){
            concents[i] = concents[i] < minTime ? 0 : concents[i] - minTime;
        }
    }

    cout << time;

    return 0;
}