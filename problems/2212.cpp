#include <iostream>
#include <vector>
#include <algorithm>
#include <queue>
using namespace std;

const int MAX_N = 10000;
const int MAX_K = 1000;

int N; // num of sensor
int K; // num of center

vector<int> sensors;
priority_queue<int> pq;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    cin >> K;

    sensors.resize(N, 0);
    for ( int n = 0; n < N; n++ ){
        cin >> sensors[n];
    }

    sort(sensors.begin(), sensors.end() );
    sensors.erase( unique(sensors.begin(), sensors.end()), sensors.end());

    for ( size_t i = 0; i < sensors.size(); i++ ){ // Debug
        cout << sensors[i] << " ";
    } cout << endl;

    for ( size_t i = 1; i < sensors.size(); i++ ){
        pq.push(sensors[i]-sensors[i-1]);
    }

    if ( sensors.size() == 1 ){
        cout << 0;
    }
    else {
        int totalRange = sensors[sensors.size()-1] - sensors[0];
        int diffSum = 0;
        for ( int k = 0; k < K-1; k++ ){
            diffSum += pq.top();
            pq.pop();
        }

        cout << totalRange - diffSum;
    }
    
    return 0;
}