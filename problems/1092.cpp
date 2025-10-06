#include <iostream>
#include <vector>
#include <algorithm>
using namespace std;

int N;
vector<int> cranes;
vector<int> craneTrgs;

int M;
vector<int> boxes;

int FindTarget( const vector<bool>& visited, int sIdx )
{
    int i = sIdx;
    for ( ;i >= 0; i-- ){
        if (visited[i] == false ){
            break;
        }
    }
    return i;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;
    cranes.resize(N);
    for ( int i = 0; i < N; i++ )
        cin >> cranes[i];
    sort(cranes.begin(), cranes.end() );
    cin >> M;
    boxes.resize(M);
    for ( int mi = 0; mi < M; mi++ )
        cin >> boxes[mi];    
    sort(boxes.begin(), boxes.end());
    
    int ans = 0;
    int left = M;
    vector<bool> visited(M, false );
    craneTrgs.resize(N);
    for ( int ci = 0; ci < N; ci++ ){
        craneTrgs[ci] = upper_bound(boxes.begin(), boxes.end(), cranes[ci] ) - boxes.begin()-1;
    }
    while ( left > 0 ){
        ans++;
        int count = 0;
        for ( int ci = 0; ci < N; ci++ ){
            if ( craneTrgs[ci] < 0 )
                continue;
                
            if ( visited[craneTrgs[ci]] == true ){
                craneTrgs[ci] = FindTarget(visited, craneTrgs[ci] );
                if ( craneTrgs[ci] < 0 )
                    continue;
            }
            
            visited[craneTrgs[ci]] = true;
            count++;

            craneTrgs[ci] = FindTarget(visited, craneTrgs[ci] );
        }

        left -= count;
        if (count == 0 )
            break;
    }

    if ( left == 0 )
        cout << ans;
    else 
        cout << -1;

    return 0;
}