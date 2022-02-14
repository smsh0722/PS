#include <iostream>
#include <set>
#include <utility>

using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false);

    set<pair<int,int>> data;
    int x, y;
    int N; cin >> N;

    for ( int i = 0; i < N; i++ ){
        cin >> x >> y;
        data.insert( pair<int,int>( x, y ) );
    }

    for ( set<pair<int,int>>::iterator it = data.begin(); it != data.end(); it++ ){
        cout << it->first << " " << it->second << "\n";
    }
}