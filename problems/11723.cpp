#include <iostream>
#include <string>
#include <cstring>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    bool data[21] = { 0 };
    int N;
    string opt;
    int x;

    cin >> N;
    for( int i = 0; i < N; i++ ){
        cin >> opt;
        if ( opt == "add" ){
            cin >> x;
            data[x] = true;
        }
        else if ( opt == "remove" ){
            cin >> x;
            data[x] = false;
        }
        else if ( opt == "check" ){
            cin >> x;
            if ( data[x] ) cout << "1";
            else           cout << "0";
        }
        else if ( opt == "toggle" ){
            cin >> x;
            if ( data[x] ) data[x] = false;
            else           data[x] = true;
        }
        else if ( opt == "all" ){
            memset( data, true, sizeof( data ) );
        }
        else {  //       "empty"
            memset( data, false, sizeof( data ) );
        }
    }
}