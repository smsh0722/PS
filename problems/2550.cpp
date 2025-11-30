#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

// # of switches
int N;
/*
2   4   1   5   3
4   5   1   3   2

    *   *       *    
5   1   3   2   4

=> LIS
*/

// switches[i] = {switch#, lis#}
vector<pair<int,int>> switches;
vector<int> bulbs;

vector<int> lis;

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    
    switches.resize(N, pair<int,int>(0,0));
    for ( int i = 0; i < N; i++ )
        cin >> switches[i].first;
    
    bulbs.resize(N+1);
    for ( int i = 0; i < N; i++ ){
        int bulb;
        cin >> bulb;
        bulbs[bulb] = i;
    }

    lis.push_back(INT32_MAX);
    for ( auto& s: switches ){
        int bulbIdx = bulbs[s.first];
        if ( lis.back() < bulbIdx ){
            lis.push_back(bulbIdx);
            s.second = lis.size() - 1;
        }
        else {
            int idx = lower_bound( lis.begin(), lis.end(), bulbIdx) - lis.begin();
            lis[idx] = bulbIdx;
            s.second = idx;
        }
    }

    vector<int> ans;
    int prevIdx = lis.size();
    for ( int i = N - 1; i >= 0; i-- ){
        if ( switches[i].second == prevIdx-1 ){
            ans.push_back(switches[i].first);
            prevIdx = switches[i].second;
        }
    }

    sort( ans.begin(), ans.end() );

    cout << ans.size() << "\n";
    for ( auto s : ans ){
        cout << s << " ";
    }

    return 0;
}