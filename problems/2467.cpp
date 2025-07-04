#include <iostream>
#include <vector>
using namespace std;

struct Vec2{
    int x,y;
};

struct MinData{
    Vec2 combination;
    int sum;
};

const int MAX_INT = ~(1<<31);
const int MAX_N = 100000;

int N;
vector<int> list(MAX_N);

inline int Abs( int a )
{
    return a < 0 ? -a : a;
}

MinData binaryFindRecursive( int src, int l, int r );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL);

    cin >> N;

    for ( int i = 0; i < N; i++ ){
        cin >> list[i];
    }

    MinData min = {{-1, -1}, MAX_INT};
    for ( int i = 0; i < N-1; i++ ){
        MinData localMin;
        localMin = binaryFindRecursive(i, i+1, N-1 );
        if ( Abs(min.sum) > Abs(localMin.sum) )
            min = localMin;
    }

    cout << list[min.combination.x] << " "
        << list[min.combination.y];
}

MinData binaryFindRecursive( int src, int l, int r )
{
    if ( l == r )
        return MinData{ Vec2{src, l}, list[src] + list[l] };

    int mid = (r-l)/2 + l;
    int sum = list[src] + list[mid];
    MinData childSum;
    if ( sum > 0 )
        childSum = binaryFindRecursive(src, l, mid );
    else
        childSum = binaryFindRecursive(src, mid+1, r);
    
    if ( Abs(sum) > Abs(childSum.sum) )
        return childSum;
    else 
        return MinData{ Vec2{src, mid}, sum};
}