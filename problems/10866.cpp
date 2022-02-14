#include <iostream>
#include <string>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    int N; cin >> N;
    int* arr = new int[2*N];

    string cLine;
    int lEnd = N;
    int rEnd = N - 1;
    for ( int i = 0; i < N; i++ ){
        cin >> cLine;
        // push_front, push_back, pop_front, pop_back, size, empty, front,back
        if ( cLine == "push_front" ){
            cin >> arr[--lEnd];
            continue;
        }
        else if ( cLine == "push_back" ){
            cin >> arr[++rEnd];
            continue;
        }
        else if ( cLine == "pop_front" ){
            if ( lEnd > rEnd ) cout << "-1\n";
            else               cout << arr[lEnd++] << "\n";
            continue;
        }
        else if ( cLine == "pop_back" ){
            if ( lEnd > rEnd ) cout << "-1\n";
            else               cout << arr[rEnd--] << "\n";
            continue;
        }
        else if ( cLine == "size" ){
            if ( lEnd > rEnd ) cout << "0\n";
            else               cout << rEnd - lEnd + 1 << "\n";
            continue;
        }
        else if ( cLine == "empty" ){
            cout << ( lEnd > rEnd ) << "\n";
            continue;
        }
        else if ( cLine == "front" ){
            if ( lEnd > rEnd ) cout << "-1\n";
            else               cout << arr[lEnd] << "\n";
            continue;
        }
        else { // cLine == "back"
            if ( lEnd > rEnd ) cout << "-1\n";
            else               cout << arr[rEnd] << "\n";
        }
    }

    return 0;
}