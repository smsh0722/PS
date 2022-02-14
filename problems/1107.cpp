#include <iostream>
using namespace std;

int count = 500001;
const int UP = 1;
const int Down = -1;
bool button[10] = { 0 }; // true = disable

void findMin( const int arr[], int Nth, int way );

int main( void )
{
    int targetArr[6] = {0};
    int target; cin >> target;

    // set button
    int temp;
    int buttonNum; cin >> buttonNum;
    for ( int i = 0; i < buttonNum; i++ ){
        cin >> temp;
        button[temp] = true;
    }
    
    int Nth = 1;
    targetArr[0] = temp % 10;
    while ( temp >= 10 ){
        temp /= 10;
        targetArr[Nth] = temp % 10;
        Nth++;
    }

    findMin( targetArr, Nth, UP );
    findMin( targetArr, Nth, Down );

    cout << count << endl;
    return 0;
}

void findMin( const int arr[], int Nth, int way ){
    
}