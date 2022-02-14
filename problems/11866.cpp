#include <iostream>
#include <list>
#include <time.h>
using namespace std;

int main( void )
{
    ios_base::sync_with_stdio( false );
    
    int size, stepN;
    cin >> size >> stepN;
    clock_t t = clock(); // Debug

    list<int> data;
    for ( int i = 1; i <= size; i++ )  data.push_back(i);

    list<int>::iterator it =  data.begin();
    cout << "<";
    while ( size > 0 ){
        int rStep = stepN % size; // real step
        rStep = rStep == 0 ? size : rStep;

        for ( int i = 1; i < rStep; i++ ){
            if ( it == data.end() ){
                it = data.begin();
                i--;
                continue;
            }
            else it++;
        }
        it = it == data.end() ? data.begin() : it;
        if ( size != 1 ) cout << *it << ", ";
        else cout << *it;
        it = data.erase( it );
        size--;
    }
    cout << ">";

    cout << "Time: " << clock() - t; // Debug
    return 0;
}