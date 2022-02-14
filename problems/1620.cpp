#include <iostream>
#include <algorithm>
#include <map>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N, M;
    
    // Set data
    cin >> N; cin >> M;
    string* data = new string[N+1];
    map<string, int> data_lib;

    for( int i = 1; i < N+1; i++ ){
        cin >> data[i];
        data_lib.insert( pair<string, int>( data[i], i) ); 
    }

    // output
    string target;
    for ( int i = 0; i < M; i++ ){
        cin >> target;

        // int target
        if ( target[0] >= '0' && target[0] <= '9' )
            cout << data[stoi(target)] << "\n";
        // string target
        else 
            cout << data_lib[target] << "\n";
    }
}