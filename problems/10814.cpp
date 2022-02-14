#include <iostream>
#include <queue>
#include <string>
using namespace std;

int main( void )
{   
    ios_base::sync_with_stdio(false);

    int N; cin >> N;
    queue<string> arr[200+1];

    int age; // 1~200
    string name;
    for ( int i = 0; i < N; i++ ){
        cin >> age >> name;
        arr[age].push(name);
    }

    for ( int i = 1; i <= 200; i++ ){
        if ( !arr[i].empty() ){
            size_t SIZE = arr[i].size();
            for ( size_t j = 0; j < SIZE; j++ ){
                cout << i << " " << arr[i].front() << "\n";
                arr[i].pop();
            }
        }
    }

    return 0;
}