#include <iostream>
#include <map>
#include <cmath>
using namespace std;

struct xy {
    int min;
    int max;
};

void plane_push( map<int,xy>& plane, int previous[], int curr[] )
{
    int x1 = previous[0];
    int x2 = curr[0];
    int y_min = previous[1] < curr[1] ? previous[1] : curr[1];
    int y_max = previous[1] > curr[1] ? previous[1] : curr[1];
    if ( x1 > x2 ){
        int tmp = x1;
        x1 = x2;
        x2 = tmp;
    }
    for ( int x = x1; x <= x2; x++ ){
        if ( plane.find(x) == plane.end() ){
            plane[x].min = y_min;
            plane[x].max = y_max;
        }
        else {
            plane[x].min = plane.at(x).min > y_min ? y_min : plane.at(x).min;
            plane[x].max = plane.at(x).max < y_max ? y_max : plane.at(x).max;
        }
    }
}

int main( void )
{
    int n;
    cin >> n;

    map<int,xy> plane;
    double result; // result = sum1 - sum2/2
    long long sum1 = 0;
    long long sum2 = 0;
    /* calculate sum2 */
    {
        int previous[2];
        int curr[2];
        cin >> curr[0] >> curr[1];
        int firstP[2] = { curr[0], curr[1] };
        for ( int i = 1; i < n; i++ ){
            previous[0] = curr[0];
            previous[1] = curr[1];
            cin >> curr[0] >> curr[1];

            plane_push( plane, previous, curr );
            
            int sum_tmp = (previous[0]-curr[0])*(previous[1]-curr[1]);
            sum_tmp = sum_tmp < 0 ? -sum_tmp : sum_tmp;
            sum2 += sum_tmp;
        }
        /* p1 and p(n-1)*/
        {
            previous[0] = curr[0];
            previous[1] = curr[1];
            plane_push( plane, previous, firstP );
            int sum_tmp = (previous[0]-curr[0])*(previous[1]-curr[1]);
            sum_tmp = sum_tmp < 0 ? -sum_tmp : sum_tmp;
            sum2 += sum_tmp;
        }
    }

    /* calculate sum1 */
    int area = 0;
    for ( map<int,xy>::iterator it = plane.begin(); it != plane.end(); it++ ){
        area = it->second.max - it->second.min;
        sum1 += area;
    }
    sum1 -= area;

    /* result */
    double sum2d2 = (double)sum2/2;
    /* round */
    {
        sum2d2 *= 10;
        sum2d2 = round(sum2d2);
        sum2d2 /= 10;
    }
    result = sum1 - sum2d2;

    cout << result << endl;
    return 0;
}