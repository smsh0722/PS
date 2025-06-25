#include <iostream>
#include <vector>
#include <cmath>
using namespace std;

int T, N;
const int MAX_POINT_SIZE = 20;
const double MAX_DIST = 200000 * 10;

typedef struct vec2{
    int x;
    int y;
} vec2;

double SearchDist( vec2 posArr[], bool selected[], int l, int minusCount);
double GetLength( vec2 v);
double CalculateDist( vec2 posArr[], bool selected[] );

int main( void )
{
    ios_base::sync_with_stdio(false); cin.tie(NULL); cout.tie(NULL);

    cin >> T;
    vec2 posArr[MAX_POINT_SIZE];
    for ( int tIdx = 0; tIdx < T; tIdx++ ){
        cin >> N;
        int x, y;
        for ( int i = 0; i < N; i++ ){
            cin >> x >> y;
            posArr[i].x = x;
            posArr[i].y = y;
        }
        bool selected[MAX_POINT_SIZE] = {false};
        printf("%.10f\n", SearchDist(posArr, selected, 0, 0 ) );
    }
}

double SearchDist( vec2 posArr[], bool selected[], int l, int minusCount)
{
    if ( minusCount == (N/2) )
        return CalculateDist( posArr, selected );
    if( l >= N )
        return MAX_DIST;
    
    double minDist = MAX_DIST;
    double temp;
    // Case 1
    selected[l] = true;
    temp = SearchDist( posArr, selected, l+1, minusCount+1);
    if (minDist > temp )
        minDist = temp;
    // Case 2
    selected[l] = false;
    temp = SearchDist( posArr, selected, l+1, minusCount);
    if ( minDist > temp )
        minDist = temp;

    return minDist;
}

double GetLength( vec2 v)
{
    return sqrt(
        pow(v.x, 2.0) + pow(v.y, 2.0)
    );
}

double CalculateDist( vec2 posArr[], bool selected[] )
{
    vec2 sumVec = vec2 { 0, 0};

    for ( int i = 0; i < N; i++ ){
        if ( selected[i] == true ){
            sumVec.x -= posArr[i].x;
            sumVec.y -= posArr[i].y;
        }
        else {
            sumVec.x += posArr[i].x;
            sumVec.y += posArr[i].y;
        }
    }

    return GetLength( sumVec );
}