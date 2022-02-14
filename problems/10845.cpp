#include <iostream>
#include <string>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int n; cin >> n;
    int* arr = new int[n];
    int lEnd = 0, rEnd = -1;
    string cLine; // command line

    for ( int i = 0; i < n; i++ ){
        cin >> cLine;

        if ( cLine == "push" ){
            rEnd++;
            cin >> arr[rEnd];
        }
        else if ( cLine == "pop" ){
            if ( lEnd <= rEnd ) {
                cout << arr[lEnd] << "\n";
                lEnd++;
            }
            else cout << -1 << "\n";
        }
        else if ( cLine == "size" ){
            cout << ( rEnd - lEnd + 1 ) << "\n";
        }
        else if ( cLine == "empty" ){
            cout << ( lEnd > rEnd ) << "\n";
        }
        else if ( cLine == "front" ){
            if ( lEnd <= rEnd ) cout << arr[lEnd] << "\n";
            else                cout << -1 << "\n";
        }
        else { // cLine == "back"
            if ( lEnd <= rEnd ) cout << arr[rEnd] << "\n";
            else                cout << -1 << "\n";
        }
    }

    return 0;
}