#include <iostream>
using namespace std;

const int SIZE = 9;

int main( void )
{
    int i, j;
    int members[SIZE];
    int sum = 0;
    for ( i = 0; i < SIZE; i++ ){
        cin >> members[i];
        sum += members[i];
    }
    
    {
        int mindx;
        for ( i = 0; i < SIZE; i++ ){
            mindx = i;
            for ( j = i + 1; j < SIZE; j++ ){
                mindx = members[mindx] > members[j] ? j : mindx;
            }
            int tmp = members[i];
            members[i] = members[mindx];
            members[mindx] = tmp;
        }
    }

    for ( i = 0; i < SIZE; i++ ){
        bool flag = false;
        for ( j = i + 1; j < SIZE; j++ ){
            if ( sum - members[i] - members[j] == 100){
                flag = true;
                break;
            }
        }
        if ( flag == true ) break;
    }

    for ( int idx = 0; idx < SIZE; idx++ ){
        if ( idx != i && idx != j )
            cout << members[idx] << "\n";
    }

    return 0;
}