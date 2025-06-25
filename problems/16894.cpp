#include <iostream>
#include <vector>

using namespace std;

const size_t MAX_NUM = 3200000;
// N <= 10,000,000,000,000 (10^13)
// N^(1/2) = 10^(6.5)
int main( void )
{
    size_t N;
    cin >> N;

    vector<bool> primeVec(MAX_NUM, true);

    for ( size_t i = 2; i < MAX_NUM; i++){
        if ( primeVec[i] == false )
            continue;

        for ( size_t j = 2; i*j < MAX_NUM; j++ ){
            primeVec[i*j] = false;
        }
    }

    size_t curNum = N;
    int count = 0;
    for ( size_t i = 2; i*i <= curNum; i++ ){
        if ( curNum == 1 )
            break;
        if ( primeVec[i] == false )
            continue;

        while ( curNum % i == 0){
            curNum /= i;
            count++;
        }
    }

    if ( curNum == 1 ){
        if ( count == 2)
            cout << "cubelover";
        else 
            cout << "koosaga";
    }
    else {
        if ( count == 1 )
            cout << "cubelover";
        else 
            cout << "koosaga";
    }

}