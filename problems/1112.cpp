#include <iostream>
#include <cmath>
#include <string>
using namespace std;

int64_t x, b;

int GetPowerLength()
{
    int l = 0;

    if ( b > 0 ){
        int trg = abs(x);
        int num = 1;
        while ( (trg / num) >= b ){
            num *= b;
            l++;
            cout << trg << " " << num << " " << trg / num << endl;
        }
    }
    else {
        int trg = x;
        int num = 1;
        while ( true ){
            int left = trg - (trg / num)*num;
            if ( )
            num *= b;
            l++;
        }
    }

    return l;
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> x >> b;

    string s;
    cout << GetPowerLength() << endl;
    if ( b > 0 ){
    }
    else {

    }

    cout << s;

    return 0;
}