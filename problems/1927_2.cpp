#include <iostream>
#include <vector>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio(false);
    cin.tie(NULL);

    vector<int> data;
    int caseN; cin >> caseN;

    int temp;
    int size = 0;
    for ( int i = 0; i < caseN; i++ ){
        cin >> temp;

        if ( temp == 0 ){
            if( size == 0 ) cout << "0\n";
            else {
                int minIdx = 0;
                for ( int i = 1; i < size; i++ ) minIdx = data[minIdx] > data[i] ? i : minIdx;
                cout << data[minIdx] << "\n";
                data.erase( data.begin() + minIdx );
                size--;
            }
        }
        else {
            size++;
            data.push_back( temp );
        }
    }
}