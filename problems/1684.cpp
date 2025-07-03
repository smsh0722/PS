#include <iostream>
#include <vector>
using namespace std;

int n;

inline int MyMoldulo( int a, int b )
{
    if ( a >= 0 )
        return a % b;
    else {
        int c = (-a) / b;
        c++;
        return (c * b) + a;
    }
}

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    vector<int> numVec;
    int maxNum = 0;
    cin >> n;
    {
        int num;
        for ( int i = 0; i < n; i++ ){
            cin >> num;
            numVec.push_back(num);
            num = num < 0 ? -num : num;
            maxNum = maxNum < num ? num : maxNum;
        }
    }

    int maxD = -1;
    for  ( int D = 1; D <= maxNum; D++ ){
        int R = MyMoldulo( numVec[0], D );
        for ( int nIdx = 1; nIdx < n; nIdx++ ){
            if ( R != MyMoldulo( numVec[nIdx], D )){
                R = -1;
                break;
            }
        }
        if ( R != -1 )
            maxD = D;
    }
    cout << maxD <<endl;
}