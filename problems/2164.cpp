#include <iostream>
#include <list>
#include <ctime>
using namespace std;

int main( void )
{
    int N, count = 0;
    list<int> card;

    // set
    cin >> N;
        clock_t t; // time
        t = clock();

    for ( int i = 1; i <= N; i++ )
        card.push_back(i);
    
    // operate
    int temp;
    while ( N - count != 1 ){
        count++;
        //remove 
        card.pop_front();
        if ( N - count == 1 )
            break;
        //change
        temp = card.front();
        card.pop_front();
        card.push_back(temp);
    }
    cout << card.front() << "\n";

    //time
    t = clock() - t;
    cout << t;
}
